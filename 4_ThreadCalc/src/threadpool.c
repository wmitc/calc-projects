#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "threadpool.h"
#include "utils.h"

/**
 * @note A queue is recommended, not required.
 */


static tpool_work_t *tpool_work_create(job_f job, void *arg)
{
    tpool_work_t *work;

    if (job == NULL)
        return NULL;

    work       = malloc(sizeof(*work));
    work->job = job;
    work->arg  = arg;
    work->next = NULL;
    return work;
}

static void tpool_work_destroy(tpool_work_t *work)
{
    if (work == NULL)
        return;
    free(work);
}

static tpool_work_t *tpool_work_get(threadpool_t *tm)
{
    tpool_work_t *work;

    if (tm == NULL)
        return NULL;

    work = tm->work_first;
    if (work == NULL)
        return NULL;

    if (work->next == NULL) {
        tm->work_first = NULL;
        tm->work_last  = NULL;
    } else {
        tm->work_first = work->next;
    }

    return work;
}

static void *tpool_worker(void *arg)
{
    threadpool_t      *tm = arg;
    tpool_work_t *work;

    while (1) {
        pthread_mutex_lock(&(tm->work_mutex));

        while (tm->work_first == NULL && !tm->stop)
            pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));

        if (tm->stop)
            break;

        work = tpool_work_get(tm);
        tm->working_cnt++;
        pthread_mutex_unlock(&(tm->work_mutex));

        if (work != NULL) {
            work->job(work->arg);
            tpool_work_destroy(work);
        }

        pthread_mutex_lock(&(tm->work_mutex));
        tm->working_cnt--;
        if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
            pthread_cond_signal(&(tm->working_cond));
        pthread_mutex_unlock(&(tm->work_mutex));
    }

    tm->thread_cnt--;
    pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
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
    // Fail if the thread count is zero
    if(thread_count == 0)
    {
        return NULL;
    }

    // Instantiate pool and thread
    threadpool_t *pool;
    pthread_t thread;

    // Instantiate the pool with calloc
    pool = calloc(1, sizeof(threadpool_t));
    // Set the thread count
    pool->thread_cnt= thread_count;
    
    pthread_mutex_init(&(pool->work_mutex), NULL);
    pthread_cond_init(&(pool->work_cond), NULL);
    pthread_cond_init(&(pool->working_cond), NULL);

    pool->work_first = NULL;
    pool->work_last = NULL;

    // Create threads
    for(size_t i = 0; i < thread_count; i++)
    {
        pthread_create(&thread, NULL, tpool_worker, pool);
        pthread_detach(thread);
    }

    return pool;
}

/**
 * @brief Implementation of the threadpool_shutdown function
 */
int threadpool_shutdown(threadpool_t * pool_p)
{
    return 0;
}

/**
 * @brief Implementation of the threadpool_destroy function
 */
int threadpool_destroy(threadpool_t ** pool_pp)
{
    return 0;
}

/**
 * @brief Implementation of the threadpool_add_job function
 */
int threadpool_add_job(threadpool_t * pool_p,
                       job_f          job,
                       free_f         del_f,
                       void *         arg_p)
{
    
    
    return SUCCESS;
}

/*** end of file ***/
