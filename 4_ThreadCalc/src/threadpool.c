#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "threadpool.h"
#include "utils.h"

#define CAPACITY 100

/**
 * @note A queue is recommended, not required.
 */

 /**
  * @brief Threadpool job struct.
  */
struct threadpool_job_t
{
    job_f job_function;
    free_f free_function;
    void *arg;
};

/**
 * @brief Threadpool struct.
 */
struct threadpool_t
{
    pthread_t *threads;
    size_t thread_count;

    queue_t *job_queue;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int shutdown;
};


static void * threadpool_worker(void * arg)
{
    threadpool_t *pool = (threadpool_t *) arg;

    while(1)
    {
        pthread_mutex_lock(&pool->mutex);

        // Wait for work or shutdown
        while(queue_emptycheck(pool->job_queue) == 0 && !pool->shutdown)
        {
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }

        // If shutdown and no jobs left, exit thread
        if(pool->shutdown && queue_emptycheck(pool->job_queue) != 0)
        {
            pthread_mutex_unlock(&pool->mutex);
            break;
        }

        // Get a job
        queue_node_t *node = queue_dequeue(pool->job_queue);
        pthread_mutex_unlock(&pool->mutex);

        if(!node)
        {
            // No job found, loop again
            continue;
        }

        threadpool_job_t *job = (threadpool_job_t *) node->data;

        // Run job function
        if(job->job_function)
        {
            job->job_function(job->arg);
        }

        // Call free function on arg if there is one
        if(job->free_function)
        {
            job->free_function(job->arg);
        }

        // Free job struct and queue node
        free(job);
        free(node);
    }

    return NULL;
}
/**
 * @brief Create a new threadpool and instantiate as required.
 *
 * @param thread_count The number of threads to create in the threadpool
 *
 * @return SUCCESS: A threadpool instance of type threadpool_t.
 *         FAILURE: NULL
 */
threadpool_t * threadpool_create(size_t thread_count)
{
    // Fail if thread_count is zero
    if(thread_count == 0)
    {
        fprintf(stderr, "[-] Thread count must be greater than 0.\n");
        return NULL;
    }

    threadpool_t *pool = malloc(sizeof(threadpool_t));
    // Check that pool instandiation was successful
    if(!pool)
    {
        fprintf(stderr, "[-] Threadpool instantiation failure.\n");
        return NULL;
    }

    // Set parameters
    pool->thread_count = thread_count;
    pool->shutdown = 0;
    pool->threads = malloc(thread_count * sizeof(pthread_t));
    // Check that malloc was successful
    if(!pool->threads)
    {
        fprintf(stderr, "[-] Thread allocation failed.\n");
        free(pool);
        return NULL;
    }

    // Initialize mutex and cond
    if(pthread_mutex_init(&pool->mutex, NULL) != 0)
    {
        free(pool->threads);
        free(pool);
        return NULL;
    }

    if(pthread_cond_init(&pool->cond, NULL) != 0)
    {
        pthread_mutex_destroy(&pool->mutex);
        free(pool->threads);
        free(pool);
        return NULL;
    }

    // Initialize job queue
    pool->job_queue = queue_init(CAPACITY, free);
    // Validate queue instantiation
    if(!pool->job_queue)
    {
        fprintf(stderr, "[-] Failed to instantiate queue.\n");
        // Destroy mutex, cond, and pool
        pthread_cond_destroy(&pool->cond);
        pthread_mutex_destroy(&pool->mutex);
        free(pool->threads);
        free(pool);        
    }

    // Create the threads
    for(size_t i = 0; i < thread_count; i++)
    {
        if(pthread_create(&pool->threads[i], NULL, threadpool_worker, pool) != 0)
        {
            // Shut it all down if thread creation failed
            pool->shutdown = 1;
            for(size_t j = 0; j < i; j++)
            {
                pthread_cond_broadcast(&pool->cond);
                pthread_join(pool->threads[j], NULL);
            }
            queue_destroy(&pool->job_queue);
            pthread_cond_destroy(&pool->cond);
            pthread_mutex_destroy(&pool->mutex);
            free(pool->threads);
            free(pool);
            return NULL;
        }
    }

    return pool;
}

/**
 * @brief Implementation of the threadpool_shutdown function
 */
int threadpool_shutdown(threadpool_t * pool_p)
{
    // Confirm pool existence
    if(!pool_p)
    {
        fprintf(stderr, "[-] Pool nonexistent.\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_lock(&pool_p->mutex);
    // Mark pool for shutdown
    pool_p->shutdown = 1;
    // Announce to all threads
    pthread_cond_broadcast(&pool_p->cond);
    pthread_mutex_unlock(&pool_p->mutex);

    // Wait for all threads to terminate
    for(size_t i = 0; i < pool_p->thread_count; i++)
    {
        pthread_join(pool_p->threads[i], NULL);
    }

    return SUCCESS;
}

/**
 * @brief Implementation of the threadpool_destroy function
 */
int threadpool_destroy(threadpool_t ** pool_pp)
{
    // Confirm pool existence
    if(!pool_pp || !*pool_pp)
    {
        fprintf(stderr, "[-] Pool nonexistent.\n");
        return EXIT_FAILURE;
    }

    threadpool_t *pool = *pool_pp;

    // Shutdown if not already done
    threadpool_shutdown(pool);

    // Destroy queue
    queue_destroy(&pool->job_queue);

    // Destroy mutex and cond
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);

    // Free threads and pool
    free(pool->threads);
    free(pool);

    // Set address to NULL to avoid dangling pointer
    *pool_pp = NULL;

    return SUCCESS;
}

/**
 * @brief Implementation of the threadpool_add_job function
 */
int threadpool_add_job(threadpool_t * pool_p,
                       job_f          job,
                       free_f         del_f,
                       void *         arg_p)
{
    
    // Confirm pool and job existence
    if(!pool_p || !job)
    {
        fprintf(stderr, "[-] Pool or job do not exist.\n");
        return EXIT_FAILURE;
    }

    pthread_mutex_lock(&pool_p->mutex);
    // Check shutdown flag
    if(pool_p->shutdown)
    {
        pthread_mutex_unlock(&pool_p->mutex);
        fprintf(stderr, "[-] Pool shutting down.\n");
        return EXIT_FAILURE;
    }

    // Start a new job
    threadpool_job_t *new_job = malloc(sizeof(threadpool_job_t));
    // Validate malloc
    if(!new_job)
    {
        fprintf(stderr, "[-] New job instantiation failure.\n");
        pthread_mutex_unlock(&pool_p->mutex);
        return EXIT_FAILURE;
    }

    // Set job parameters
    new_job->job_function = job;
    new_job->free_function = del_f;
    new_job->arg = arg_p;

    // Enqueue the job
    if(queue_enqueue(pool_p->job_queue, new_job) != 0)
    {
        fprintf(stderr, "[-] Failed to enqueue job.\n");
        free(new_job);
        pthread_mutex_unlock(&pool_p->mutex);
        return EXIT_FAILURE;
    }

    // Signal that job has been added to queue
    pthread_cond_signal(&pool_p->cond);
    pthread_mutex_unlock(&pool_p->mutex);

    return SUCCESS;
}

/*** end of file ***/
