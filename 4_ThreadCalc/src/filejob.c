#include <stdio.h>
#include "threadpool.h"   
#include "process_file.h" 
#include "filejob.h"

void * run_filejob(void *arg)
{
    if(arg == NULL)
    {
        fprintf(stderr, "[-] NULL argument passed to run_filejob.\n");
    }
    
    filejob_t *job = (filejob_t *) arg; 
  
    // Process the file
    process_file(job->filename, job->input_dir, job->output_dir);
}

void free_filejob(void *arg)
{
    filejob_t *job = (filejob_t *) arg;

    if(!job)
    {
        fprintf(stderr, "[-] NULL argument passed to free_filejob.\n");
    }
    // do we need to free them all?
    free(job->filename);
    free(job->input_dir);
    free(job->output_dir);
    free(job);
}
