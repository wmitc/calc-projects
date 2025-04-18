#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "types.h"
#include "evaluate.h"

#define MAX_PATH_LENGTH 256
#define MAGIC_NUMBER 0xdd77bb55
#define MEM_PERMISSIONS 0644

int process_file(const char *file, const char *input_dir, const char *output_dir){
    //printf("%s\n",file);

    char input_path[MAX_PATH_LENGTH];
    memset(input_path, 0, sizeof(input_path));
   
    strcat(input_path, input_dir);
    strcat(input_path, "/");
    strcat(input_path, file);
    //printf("%s\n", input_path);
    
    int fd = open(input_path,O_RDONLY);
    //printf("%d\n", fd);

    if(fd < 0){
        fprintf(stderr, "[-] Failed to open file for reading.\n");
        return 1;
    }

    // FILE PERMISSIONS CHECK??

    file_header header;
    if(read(fd, &header, sizeof(header)) != sizeof(header)){
        fprintf(stderr, "[-] Failed to read header.\n");
        close(fd);
        return 1;
    }

    // Validate the magic number
    if(header.magic_number != MAGIC_NUMBER){
        fprintf(stderr, "[-] Unexpected magic number.\n");
        close(fd);
        return 1;
    }

    //printf("%x\n", header.magic_number);
    //printf("%lx\n", header.fileID);
    //printf("%lx\n", header.num_of_equations);
    //printf("%x\n", header.flag);
    //printf("%x\n", header.offset);
    //printf("%x\n", header.num_of_opt_headers);
    
    // Set file offset of open file descriptor to header.offset
    if(lseek(fd, header.offset, SEEK_SET) == -1){
        fprintf(stderr, "[-] Failed to move file offset.\n");
        close(fd);
        return 1;        
    }

    // Allocate space for all solved equations in an array
    solved_equation *solves = malloc(header.num_of_equations * sizeof(solved_equation));

    if(!solves){
        fprintf(stderr, "[-] Failed to allocate space for solved equations.\n");
        close(fd);
        return 1;
    }

    for(int64_t i = 0; i < header.num_of_equations; i++){
        unsolved_equation unsolved_equ;
        if(read(fd, &unsolved_equ, sizeof(unsolved_equation)) != sizeof(unsolved_equation)){
            fprintf(stderr, "[-] Failed to read equation.\n");
            close(fd);
            return 1;       
        }

        // Attemt to solve equation
        int64_t solution;
        int8_t type;
        // Initiate "solved" variable to 0 to indicate unsolved
        int solved = 0;
        solved = evaluate_equation(unsolved_equ.operand1, unsolved_equ.operation, unsolved_equ.operand2, &solution, &type);

        //printf("Op1: %lx\n", unsolved_equ.operand1);
        //printf("Operand: %x\n", unsolved_equ.operation);
        //printf("Op2: %lx\n", unsolved_equ.operand2);

        int64_t result;
        //printf("Solved: %d\n", solved);
        //printf("%d\n", type);
        //printf("%ld\n", solution);

        // Put data into solves array
        solves[i].equationID = unsolved_equ.equationID;
        solves[i].flag = solved;
        solves[i].type = type;
        solves[i].solution = solution;


    }
    // Clean up
    close(fd);

    // Now handloe writing results to file
  
    char output_path[MAX_PATH_LENGTH];
    memset(output_path, 0, sizeof(output_path));
   
    strcat(output_path, output_dir);
    strcat(output_path, "/");
    strcat(output_path, file);
    //printf("%s\n", output_path);

    fd = open(output_path, O_CREAT | O_WRONLY | O_TRUNC, MEM_PERMISSIONS);
    if(fd < 0){
        fprintf(stderr, "[-] Failed to open file for writing.\n");
        return 1;
    }

    // Set header flag to indicated solved
    header.flag = 0x1;
    // Write header to file
    if(write(fd, &header, sizeof(header)) != sizeof(header)){
        fprintf(stderr, "[-] Failed to write header.\n");
        close(fd);
        return 1;
    }
    // Write all saved equations to file
    for(int64_t i = 0; i < header.num_of_equations; i++){
        if(write(fd, &solves[i], sizeof(solved_equation)) != sizeof(solved_equation)){
            fprintf(stderr, "[-] Failed to write equation.\n");
            close(fd);
            return 1;       
        }        
    }

    // Clean up
    close(fd);

    return 0;
}
