/* file_job.h --------------------------------------------------- */
#ifndef FILE_JOB_H
#define FILE_JOB_H

#include "threadpool.h"   /* job_f / free_f typedefs */
#include "process_file.h" /* prototype of process_file */

/* What each job needs to know */
typedef struct {
    char *filename;     /* entry->d_name copy              */
    char *input_dir;    /* copy or original string literal */
    char *output_dir;   /* copy or original string literal */
} file_job_t;

/* --------------------------------- job function ---------- */
void file_job(void *arg);


/* --------------------------------- optional cleanup ------ */
void file_job_free(void *arg);

#endif /* FILE_JOB_H */

