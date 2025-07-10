#include <dirent.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "filejob.h"
#include "file_io.h"
#include "process_file.h"
#include "shared_mutex.h"
#include "threadpool.h"

/**
 * @brief Validate whether input string is a directory
 *
 * @param dir User provided directory parameter
 * @return True/False if/if not *dir is a directory
 */
int is_directory(const char *dir)
{
    struct stat statbuf;
    if (stat(dir, &statbuf) != 0)
    {
        fprintf(stderr, "[-] Error: path does not exist or is inaccessible.\n");
        exit(EXIT_FAILURE);
    }

    return S_ISDIR(statbuf.st_mode);
}

/**
 * @brief Process input_dir and out_dir per FileCalc specification
 *
 * @param input_dir User supplied input directory
 * @param output_dir User supplied output directory
 * @return True/False on success/failure
 */
int process_dir(const char *input_dir, const char *output_dir)
{
    const char *dir_path = input_dir;
    DIR *dir             = opendir(dir_path);

    if (dir == NULL)
    {
        fprintf(stderr, "[-] Open input directory failed.");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip . and .. entries
        if (strncmp(entry->d_name, ".", strlen(entry->d_name)) != 0
            && strncmp(entry->d_name, "..", strlen(entry->d_name)) != 0)
        {
            // Call function to process file
            process_file(entry->d_name, input_dir, output_dir);
        }
    }

    closedir(dir);

    return 0;
}

/**
 * @brief Process input_dir and out_dir per FileCalc specification
 *
 * @param input_dir User supplied input directory
 * @param output_dir User supplied output directory
 * @return True/False on success/failure
 */
int process_dir_threaded(threadpool_t *pool,
                         const char *input_dir,
                         const char *output_dir)
{
    const char *dir_path = input_dir;
    DIR *dir             = opendir(dir_path);

    if (dir == NULL)
    {
        fprintf(stderr, "[-] Open input directory failed.");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    int cnt = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip . and .. entries
        if (strncmp(entry->d_name, ".", strlen(entry->d_name)) != 0
            && strncmp(entry->d_name, "..", strlen(entry->d_name)) != 0)
        {
            // Set up file_job
            filejob_t *job = malloc(sizeof(filejob_t));

            if (!job)
            {
                closedir(dir);
                return EXIT_FAILURE;
            }

            // Malloc all parameters going to a thread via strdup
            job->filename   = strdup(entry->d_name);
            job->input_dir  = strdup(input_dir);
            job->output_dir = strdup(output_dir);

            // Add job to threadpool for processing
            if (threadpool_add_job(pool, run_filejob, free_filejob, job)
                != SUCCESS)
            {
                fprintf(stderr, "[-] Failed to add job to threadpool.\n");
                free_filejob(job);
                closedir(dir);
                return EXIT_FAILURE;
            }
            else
            {
                cnt++;
                pthread_mutex_lock(&printf_mutex);
                printf("[*] Job %d added to pool\n", cnt);
                pthread_mutex_unlock(&printf_mutex);
            }

            // Call function to process file
            // process_file(entry->d_name, input_dir, output_dir);
        }
    }
    // Shut down the thread pool
    threadpool_shutdown(pool);

    // Print info to console
    pthread_mutex_lock(&printf_mutex);
    printf("[+] Shut down the threadpool\n");
    pthread_mutex_unlock(&printf_mutex);

    // Destroy the threadpool
    threadpool_destroy(&pool);

    // Print info to console
    pthread_mutex_lock(&printf_mutex);
    printf("[+] Destroyed the threadpool\n");
    pthread_mutex_unlock(&printf_mutex);

    // Close input directory
    closedir(dir);

    return 0;
}

/*** end of file ***/
