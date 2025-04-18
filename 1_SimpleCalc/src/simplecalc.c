// src/simplecalc.c
// This file makes computations based on user input and math_utils.h
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"


int main(int argc, char *argv[]){
    if(argc <= 1){
        printf("No arguments provided\n");
        
        return 1;
    }

    if(argc != 4){
        printf("Usage: %s <number 1> <operation> <number 2>\n", argv[0]);
    
        return 1;
    }
    
    // Parse the command-line arguments
    int32_t num1 = atoi(argv[1]);
    char *op = argv[2];
    int32_t num2 = atoi(argv[3]);  
    //printf("Hello world!\n");        
    printf("%d",num1); printf("\n");
    printf("%s",op); printf("\n");
    printf("%d",num2); printf("\n");

    // Variable to hold result
    int32_t result = 0;

    // Perform operation on given numers
    if(strcmp(op, "+") == 0){
        result = add(num1, num2);
    }
    if(strcmp(op, "-") == 0){
        result = subtract(num1, num2);
    }
    if(strcmp(op, "*") == 0){
        result = multiply(num1, num2);
    }
    if(strcmp(op, "/") == 0){
        result = divide(num1, num2);
    }
    if(strcmp(op, "%") == 0){
        result = modulo(num1,num2);
    }
    if(strcmp(op, "<<") == 0){
        result = shift_left((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, ">>") == 0){
        result = shift_right((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, "&") == 0){
        result = bitwise_and((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, "|") == 0){
        result = bitwise_or((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, "^") == 0){
        result = bitwise_xor((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, "<<<") == 0){
        result = rotate_left((uint64_t)num1, (uint64_t)num2);
    }
    if(strcmp(op, ">>>") == 0){
        result = rotate_right((uint64_t)num1, (uint64_t)num2);
    }

    if(result == -1){
        printf("[-] Error processing.");
        exit(EXIT_FAILURE);
    }
    
    printf("[+] Result: %d\n", result);
    
    return 0; 
}
