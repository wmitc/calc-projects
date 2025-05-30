#include <stdio.h>
#include "filejob.h"
#include "process_file.h"
#include "threadpool.h"

void *run_filejob(void *arg)
{
    // Validate arg
    if (arg == NULL)
    {
        fprintf(stderr, "[-] NULL argument passed to run_filejob.\n");
        
        return NULL;
    }

    // Extract filejob_t data from *arg
    filejob_t *job = (filejob_t *)arg;

    // Process the file
    process_file(job->filename, job->input_dir, job->output_dir);
}

void free_filejob(void *arg)
{
    // Extract filejob_t data from *arg
    filejob_t *job = (filejob_t *)arg;

    if (!job)
    {
        fprintf(stderr, "[-] NULL argument passed to free_filejob.\n");
    }

    // Free all malloc'd data within job, then free job
    free(job->filename);
    free(job->input_dir);
    free(job->output_dir);
    free(job);
}

/*** end of file ***/
