#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "math_utils.h"
#include "evaluate.h"

/**
 * @brief Execute the specified operation on the user-supplied operands
 * 
 * @param num1 First operand
 * @param operation Operator
 * @param num2 Second operand
 * @param result Field to store result of computation
 * @param type Field to store type specification based on operation
 * @return int64_t Solved? True/False
 */
int64_t evaluate_equation(int64_t num1, int8_t operation, int64_t num2, int64_t *result, int8_t *type){
    // Use switch to determine and perform operation
    switch(operation){
        case 0x1:
            *result = add(num1, num2);
            *type  = 0x1;
            break;
        case 0x2:
            *result = subtract(num1, num2);
            *type  = 0x1;
            break;
        case 0x3:
            *result = multiply(num1, num2);
            *type  = 0x1;
            break;
        case 0x4:
            *result = divide(num1, num2);
            *type  = 0x1;
            break;
        case 0x5:
            *result = modulo(num1, num2);
            *type  = 0x1;
            break;
        case 0x6:
            *result = shift_left(num1, num2);
            *type  = 0x2;
            break;
        case 0x7:
            *result = shift_right(num1, num2);
            *type  = 0x2;
            break;
        case 0x8:
            *result = bitwise_and(num1, num2);
            *type  = 0x2;
            break;
        case 0x9:
            *result = bitwise_or(num1, num2);
            *type  = 0x2;
            break;
        case 0xa:
            *result = bitwise_xor(num1, num2);
            *type  = 0x2;
            break;
        case 0xb:
            *result = rotate_left(num1, num2);
            *type  = 0x2;
            break;
        case 0xc:
            *result = rotate_right(num1, num2);
            *type  = 0x2;
            break;
        default:
            fprintf(stderr, "[-] Invalid operation.");
            return -1;
    }

    // In this circumstance, return 1 to indicate equation was solved
    return 1;
}

