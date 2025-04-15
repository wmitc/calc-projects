#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include "file_io.h"

/*
 * Validate whether input string is a directory
 * @param dir User provided directory parameter
 * @return True/False if/if not *dir is a directory
 */
int is_directory(const char *dir){
    struct stat statbuf;
    if(stat(dir, &statbuf) != 0){
        fprintf(stderr, "[-] Error: path does not exist or is inaccessible.\n");
        exit(EXIT_FAILURE);
    }

    return S_ISDIR(statbuf.st_mode);
}

/*
 * Process input_dir and out_dir per FileCalc specification
 * @param input_dir User supplied input directory
 * @param output_dir User supplied output directory
 * @return True/False on success/failure
 */
int process_dir(const char *input_dir, const char *output_dir){
    const char *dir_path = "./input_dir";
    DIR *dir = opendir(dir_path);

    if(dir == NULL){
        fprintf(stderr, "[-] Open input directory failed.");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    errno = 0;
    while((entry = readdir(dir)) != NULL){
        // Skip . and ..
        if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
            
            // Call function to process dir, but hold on for now
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);

    return 0;
}
