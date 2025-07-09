#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pollserver.h"

#define DEFAULT_THREADPOOL_SIZE 4
#define MAXIMUM_THREADPOOL_SIZE 16
#define MIN_ARGC 3
#define MAC_ARGC 5
#define BASE10 10

int main(int argc, char *argv[])
{

    // Instantiate threadpool with user provided or default size
    // size_t pool_size = (n_set ? (size_t)num_threads :
    // DEFAULT_THREADPOOL_SIZE); threadpool_t *pool =
    // threadpool_create(pool_size);

    // Start the server
    pollserver();
}

/*** end of file ***/
