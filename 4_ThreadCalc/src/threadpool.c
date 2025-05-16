#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <threadpool.h>
#include "utils.h"

/**
 * @note A queue is recommended, not required.
 */
#include "queue.h"

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
    return NULL;
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
    return 0;
}

/*** end of file ***/
