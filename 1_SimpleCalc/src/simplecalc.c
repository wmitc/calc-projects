// src/simplecalc.c
// This file makes computations based on user input and math_utils.h
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "math_utils.h"

#define BASE10 10

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
    char *op = argv[2];

    char *endptr;
    errno = 0; // Set errno to 0 before strtol call
    long long_num1 = strtol(argv[1], &endptr, BASE10);

    // Check for errors
    if(errno == ERANGE)
    {
        fprintf(stderr, "[-] strtol range error!\n");
        return 1;
    }
    if(*endptr != '\0')
    {
        fprintf(stderr, "[-] bad input error!\n");
        return 1;
    }
    if(long_num1 < INT32_MIN || long_num1 > INT32_MAX)
    {
        fprintf(stderr, "[-] integer overflow error!\n");
        return 1;
    }   
    errno = 0; // Set errno to 0 before strtol call
    long long_num2 = strtol(argv[3], &endptr, BASE10);  

    // Check for errors
    if(errno == ERANGE)
    {
        fprintf(stderr, "[-] strtol range error!\n");
        return 1;
    }
    if(*endptr != '\0')
    {
        fprintf(stderr, "[-] malformed input error!\n");
        return 1;
    }
    if(long_num2 < INT32_MIN || long_num2 > INT32_MAX)
    {
        fprintf(stderr, "[-] integer overflow error!\n");
        return 1;
    }  
    
    // Cast long_num1 and long_num2 as int32_t
    int32_t num1 = (int32_t) long_num1;
    int32_t num2 = (int32_t) long_num2;

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
        printf("got here\n");
        result = shift_left(num1, num2);
    }
    if(strcmp(op, ">>") == 0){
        result = shift_right(num1, num2);
    }
    if(strcmp(op, "&") == 0){
        result = bitwise_and(num1, num2);
    }
    if(strcmp(op, "|") == 0){
        result = bitwise_or(num1, num2);
    }
    if(strcmp(op, "^") == 0){
        result = bitwise_xor(num1, num2);
    }
    if(strcmp(op, "<<<") == 0){
        result = rotate_left(num1, num2);
    }
    if(strcmp(op, ">>>") == 0){
        result = rotate_right(num1, num2);
    }
    printf("[+] Result: %d\n", result);
    
    return 0; 
}
