#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "types.h"
#include "evaluate.h"

#define MAX_PATH_LENGTH 256
#define MAGIC_NUMBER 0xdd77bb55 // Hard-coded file header "magic number" value used for testing
#define MEM_PERMISSIONS 0644
#define FULL_PERMISSIONS 0777

int process_file(const char* file, const char* input_dir,
                 const char* output_dir)
{
    // Build input directory path based on input_dir and file name
    char input_path[MAX_PATH_LENGTH];
    memset(input_path, 0, sizeof(input_path));

    strcat(input_path, input_dir);
    strcat(input_path, "/");
    strcat(input_path, file);

    // Open file
    int fd = open(input_path, O_RDONLY);

    if (fd < 0)
    {
        fprintf(stderr, "[-] Failed to open file for reading.\n");
        return 1;
    }

    // Extract file type and permission bits

    // KNOWN ISSUE: Test script produce files with with 0664 permissions instead
    // of 0644

    /*struct stat fileStat;
    if(stat(input_path, &fileStat) < 0)
    {
        fprintf(stderr, "[-] Failed to read file permissions.\n");
    }
    // Isolate permission bits
    mode_t permissions = fileStat.st_mode & FULL_PERMISSIONS;
    // Check 0644 permissions
    //print("Permissions: %o\n", permissions);
    if(permissions != MEM_PERMISSIONS)
    {
        fprintf(stderr, "[-] %s does not have 0644 file permissions. %o\n",
    file, permissions); return 1;
    }*/

    // Read in file header information
    file_header header;
    if (read(fd, &header, sizeof(header)) != sizeof(header))
    {
        fprintf(stderr, "[-] Failed to read header.\n");
        close(fd);
        return 1;
    }

    // Validate the magic number
    if ((unsigned) header.magic_number != (unsigned) MAGIC_NUMBER)
    {
        fprintf(stderr, "[-] Unexpected magic number.\n");
        close(fd);
        return 1;
    }

    // Set file offset of open file descriptor to header.offset
    if (lseek(fd, header.offset, SEEK_SET) == -1)
    {
        fprintf(stderr, "[-] Failed to move file offset.\n");
        close(fd);
        return 1;
    }

    // Allocate space for all solved equations in an array
    solved_equation* solves =
        malloc(header.num_of_equations * sizeof(solved_equation));

    if (!solves)
    {
        fprintf(stderr, "[-] Failed to allocate space for solved equations.\n");
        close(fd);
        return 1;
    }

    for (int64_t i = 0; i < header.num_of_equations; i++)
    {
        unsolved_equation unsolved_equ;
        if (read(fd, &unsolved_equ, sizeof(unsolved_equation)) !=
            sizeof(unsolved_equation))
        {
            fprintf(stderr, "[-] Failed to read equation.\n");
            close(fd);
            return 1;
        }

        // Initiate type variable to differentiate int64_t and uint64_t problems
        int8_t type;
        // Initiate "solved" variable to 0 to indicate unsolved
        int solved = 0;
        // Attempt to solve equation
        if (unsolved_equ.operation >= 0x1 && unsolved_equ.operation <= 0x5)
        {
            int64_t signed_solution;

            solved = evaluate_signed_equation(
                unsolved_equ.operand1, unsolved_equ.operation,
                unsolved_equ.operand2, &signed_solution, &type);

            // Put data into solves array
            solves[i].equationID = unsolved_equ.equationID;
            solves[i].flag = solved;
            solves[i].type = type;
            solves[i].solution = signed_solution;
        }
        else if (unsolved_equ.operation >= 0x6 && unsolved_equ.operation <= 0xc)
        {
            uint64_t unsigned_solution;
            
            solved = evaluate_unsigned_equation(
                unsolved_equ.operand1, unsolved_equ.operation,
                unsolved_equ.operand2, &unsigned_solution, &type);

            // Put data into solves array
            solves[i].equationID = unsolved_equ.equationID;
            solves[i].flag = solved;
            solves[i].type = type;
            solves[i].solution = (int64_t) unsigned_solution;
        }
    }
    // Clean up
    close(fd);

    // Now handle writing results to file

    char output_path[MAX_PATH_LENGTH];
    memset(output_path, 0, sizeof(output_path));

    // Build input directory path based on input_dir and file name
    strcat(output_path, output_dir);
    strcat(output_path, "/");
    strcat(output_path, file);

    fd = open(output_path, O_CREAT | O_WRONLY | O_TRUNC, MEM_PERMISSIONS);
    if (fd < 0)
    {
        fprintf(stderr, "[-] Failed to open file for writing.\n");
        return 1;
    }

    // Set header flag to indicated solved
    header.flag = 0x1;
    // Write header to file
    if (write(fd, &header, sizeof(header)) != sizeof(header))
    {
        fprintf(stderr, "[-] Failed to write header.\n");
        close(fd);
        return 1;
    }
    // Write all saved equations to file
    for (int64_t i = 0; i < header.num_of_equations; i++)
    {
        if (write(fd, &solves[i], sizeof(solved_equation)) !=
            sizeof(solved_equation))
        {
            fprintf(stderr, "[-] Failed to write equation.\n");
            close(fd);
            return 1;
        }
    }

    // Clean up
    close(fd);
    free(solves);

    printf("[+] Operation complete. See %s for results.\n", output_path);

    return 0;
}
/*** end of file ***/
