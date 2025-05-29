#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "threadpool.h"
#include "shared_mutex.h"

#define DEFAULT_THREADPOOL_SIZE 4
#define MAXIMUM_THREADPOOL_SIZE 16
#define MIN_ARGC 3
#define MAC_ARGC 5
#define BASE10 10

int main(int argc, char* argv[])
{
    // Validate number of command line arguments
    if (argc < MIN_ARGC || argc > MAC_ARGC)
    {
        pthread_mutex_lock(&printf_mutex);
        printf("Usage: %s <input_dir> <output_dir> [-n <num>]\n", argv[0]);
        printf("----------------------------------\n");
        printf("    -n number of threads\n");
        printf("       Default is 4 threads. Max is 4 threads.\n");
        pthread_mutex_unlock(&printf_mutex);
        exit(EXIT_FAILURE);
    }

    // Validate input_dir and output_dir are directories
    if (!is_directory(argv[1]) || !is_directory(argv[2]))
    {
        fprintf(stderr, "Both arguments must be directories.\n");
        exit(EXIT_FAILURE);
    }

    // Get optional -n parameter
    int opt;
    // Instantiate strtol parameters
    char *endptr;
    errno = 0; // Set errno to 0 before strtol call
    long long_n;
    // Bool to check if -n was set
    int n_set = 0;
    while((opt = getopt(argc, argv, "-n:")) != -1)
    {
        switch(opt)
        {
            // Capture mandatory -n parameter
            case 'n':
                long_n = strtol(optarg, &endptr, BASE10);
                n_set = 1;
                break;
        }
    }

    // Check for strtol errors
    if (errno == ERANGE)
    {
        fprintf(stderr, "[-] Range error on input!\n");
    }
    if(*endptr != '\0')
    {
        fprintf(stderr, "[-] Non-null string termination.\n");
    }

    // Process files from input_dir to output_dir
    /*if (process_dir(argv[1], argv[2]) != 0)
    {
        fprintf(stderr, "Error processing directory.\n");
        exit(EXIT_FAILURE);
    }*/

    pthread_mutex_lock(&printf_mutex);
    printf("[+] Program started succssfully\n");
    pthread_mutex_unlock(&printf_mutex);

    size_t num_threads = (size_t) long_n;
    if(num_threads > DEFAULT_THREADPOOL_SIZE)
    {
        num_threads = MAXIMUM_THREADPOOL_SIZE;
    }

    printf("NUMTHREADS: %d\n", num_threads);
    // Instantiate threadpool with user provided or default size
    size_t pool_size = (n_set ? (size_t) num_threads : DEFAULT_THREADPOOL_SIZE);
    threadpool_t * pool = threadpool_create(pool_size);
    
    if (process_dir_threaded(pool, argv[1], argv[2]) != 0)
    {
        fprintf(stderr, "Error processing directory.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*** end of file ***/
