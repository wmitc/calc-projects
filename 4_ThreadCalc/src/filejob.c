#include <stdio.h>
#include "threadpool.h"   
#include "process_file.h" 
#include "filejob.h"

void * run_filejob(void *arg)
{
    if(arg == NULL)
    {
        fprintf(stderr, "[-] NULl argument passed to run_filejob.\n");
    }
    
    filejob_t *job = (filejob_t *) arg; 

    printf("filename: %s\n", job->filename);
    printf("input_dir: %s\n", job->input_dir);
    printf("output_dir: %s\n", job->output_dir);
    
    // Process the file
    process_file(job->filename, job->input_dir, job->output_dir);
}

void free_filejob(void *arg)
{

    filejob_t *job = (filejob_t *) arg;

    if(!job)
    {
        fprintf(stderr, "[-] NULl argument passed to free_filejob.\n");
    }
    // do we need to free them all?
    free(job->filename);
    free(job);
}
