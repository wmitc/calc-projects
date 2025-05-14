// src/simplecalc.c
// This file makes computations based on user input and math_utils.h

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "math_utils.h"

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printf("No arguments provided\n");

        return 1;
    }

    if (argc != 4)
    {
        printf("Usage: %s <number 1> <operation> <number 2>\n", argv[0]);

        return 1;
    }

    // Parse the operation argument
    char* op = argv[2];

    // Consider int32_t operations first
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 ||
        strcmp(op, "/") == 0 || strcmp(op, "%") == 0)
    {
        int32_t result = 0;
        int32_t error = 0;
        int32_t num1 = atoi(argv[1]);
        int32_t num2 = atoi(argv[3]);
        // Perform operation on given numbers
        if (strcmp(op, "+") == 0)
        {
            result = add(num1, num2, &error);
        }
        if (strcmp(op, "-") == 0)
        {
            result = subtract(num1, num2, &error);
        }
        if (strcmp(op, "*") == 0)
        {
            result = multiply(num1, num2, &error);
        }
        if (strcmp(op, "/") == 0)
        {
            result = divide(num1, num2, &error);
        }
        if (strcmp(op, "%") == 0)
        {
            result = modulo(num1, num2, &error);
        }
        if (result == 1 && error)
        {
            printf("[-] Error processing.");
            exit(EXIT_FAILURE);
        }

        printf("[+] Result: %d\n", result);
    }
    else if (strcmp(op, "<<") == 0 || strcmp(op, ">>") == 0 ||
             strcmp(op, "&") == 0 || strcmp(op, "|") == 0 ||
             strcmp(op, "^") == 0 || strcmp(op, "<<<") == 0 ||
             strcmp(op, ">>>") == 0)
    {
        uint32_t result = 0;
        int32_t error = 0;
        uint32_t num1 = atoi(argv[1]);
        uint32_t num2 = atoi(argv[3]);

        if (strcmp(op, "<<") == 0)
        {
            result = shift_left(num1, num2, &error);
        }
        if (strcmp(op, ">>") == 0)
        {
            result = shift_right(num1, num2, &error);
        }
        if (strcmp(op, "&") == 0)
        {
            result = bitwise_and(num1, num2, &error);
        }
        if (strcmp(op, "|") == 0)
        {
            result = bitwise_or(num1, num2, &error);
        }
        if (strcmp(op, "^") == 0)
        {
            result = bitwise_xor(num1, num2, &error);
        }
        if (strcmp(op, "<<<") == 0)
        {
            result = rotate_left(num1, num2, &error);
        }
        if (strcmp(op, ">>>") == 0)
        {
            result = rotate_right(num1, num2, &error);
        }
        if (result == 1 && error)
        {
            printf("[-] Error processing.\n");
            exit(EXIT_FAILURE);
        }

        printf("[+] Result: %d\n", result);
    }
    else
    {
        printf("[-] Error processing.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
