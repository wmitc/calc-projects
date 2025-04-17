#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "types.h"

#define MAX_PATH_LENGTH 256
#define MAGIC_NUMBER 0xdd77bb55

int process_file(const char *file, const char *input_dir, const char *output_dir){
    printf("%s\n",file);

    char input_path[MAX_PATH_LENGTH];
    memset(input_path, 0, sizeof(input_path));

    //strcat(input_path, "./");     
    strcat(input_path, input_dir);
    strcat(input_path, "/");
    strcat(input_path, file);
    printf("%s\n", input_path);
    
    int fd = open(input_path,O_RDONLY);
    printf("%d\n", fd);

    if(fd < 0){
        fprintf(stderr, "[-] Failed to open file.\n");
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

    printf("%x\n", header.magic_number);
    printf("%lx\n", header.fileID);
    printf("%lx\n", header.num_of_equations);
    printf("%x\n", header.flag);
    printf("%x\n", header.offset);
    printf("%x\n", header.num_of_opt_headers);
    
    // Set file offset of open file descriptor to header.offset
    if(lseek(fd, header.offset, SEEK_SET) == -1){
        fprintf(stderr, "[-] Failed to move file offset.\n");
        close(fd);
        return 1;        
    }

    // Read in the first equation
    unsolved_equation equ;
    if(read(fd, &equ, sizeof(unsolved_equation)) != sizeof(unsolved_equation)){
        fprintf(stderr, "[-] Failed to read equation.\n");
        close(fd);
        return 1;       
    }

    printf("%x\n", equ.equationID);
    printf("%x\n", equ.flag);
    
    
    printf("%x\n", (int8_t*)equ.equation+8);
    
    solved_equation solves[header.num_of_equations];
    // Clean up
    close(fd);
  

    return 0;
}
