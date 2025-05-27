// includes/file_io.h
// This header includes functions for validating and processing directories
#ifndef FILE_IO_H
#define FILE_IO_H

#include "threadpool.h"

/**
 * @brief Determine if input string is a directory
 * 
 * @param dir String value
 * @return int True/False 
 */
int is_directory(const char* dir);

/**
 * @brief Process the directory according to specification
 * 
 * @param input_dir Input directory
 * @param output_dir Output Directory
 * @return int SUCCESS/FAILURE
 */
int process_dir(const char* input_dir, const char* output_dir);

/**
 * @brief Process directory with threads
 * 
 * @param pool Threadpool
 * @param input_dir Input directory
 * @param output_dir Output Directory
 * @return int SUCCESS/FAILURE
 */
int process_dir_threaded(threadpool_t *pool, const char* input_dir, const char* output_dir);

#endif
