#ifndef FILEJOB_H
#define FILEJOB_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A filejob type.
 */
typedef struct filejob_t 
{
    char *filename;
    char *input_dir;
    char *output_dir;  
} filejob_t;

/**
 * @brief Run a filejob
 * 
 * @param arg 
 */
void * run_filejob(void *arg);

/**
 * @brief Free a filejob
 * 
 * @param arg 
 */
void free_filejob(void *arg);

#endif