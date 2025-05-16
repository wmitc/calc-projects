#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Implementation of the job_f function
 */
void job_f(void *mem_addr)
{
    if (mem_addr)
    {
        free(mem_addr);
    }
}

/**
 * @brief Implementation of the custom_free function
 */
void free_f(void *mem_addr)
{
    if (mem_addr)
    {
        free(mem_addr);
    }
}

/*** end of file ***/
