// includes/file_io.h
// This header includes functions for validating and processing directories
#ifndef FILE_IO_H
#define FILE_IO_H

#include "threadpool.h"

int is_directory(const char* dir);
int process_dir(const char* input_dir, const char* output_dir);
int process_dir_threaded(threadpool_t *pool, const char* input_dir, const char* output_dir);

#endif
