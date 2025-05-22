#include <stdio.h>
#include "threadpool.h"   /* job_f / free_f typedefs */
#include "process_file.h" /* prototype of process_file */
#include "filejob.h"


void file_job(void *arg)
{
    printf("made it here\n");
    if(arg == NULL)
    {
        printf("arg was null!\n");
    }
    
    file_job_t *job = (file_job_t *)arg;

    printf("filename: %s\n", job->filename);
    printf("input_dir: %s\n", job->input_dir);
    printf("output_dir: %s\n", job->output_dir);
    /* run the real work */
    process_file(job->filename, job->input_dir, job->output_dir);
}

void file_job_free(void *arg)
{
    file_job_t *job = (file_job_t *)arg;
    free(job->filename);
    /* If you duplicated input/output dir strings, free them here too */
    free(job);
}
