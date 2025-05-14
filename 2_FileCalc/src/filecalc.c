#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

int main(int argc, char* argv[])
{
    // Validate number of command line arguments
    if (argc != 3)
    {
        printf("Usage: %s <input_dir> <output_dir>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Validate input_dir and output_dir are directories
    if (!is_directory(argv[1]) || !is_directory(argv[2]))
    {
        fprintf(stderr, "Both arguments must be directories.\n");
        exit(EXIT_FAILURE);
    }

    // Process files from input_dir to output_dir
    if (process_dir(argv[1], argv[2]) != 0)
    {
        fprintf(stderr, "Error processing directory.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
/*** end of file ***/
