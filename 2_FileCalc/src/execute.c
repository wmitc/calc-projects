#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "math_utils.h"
#include "execute.h"

/**
 * @brief Execute the specified operation on the user-supplied operands
 * 
 * @param equation 17 bit representing an equation 
 * @param result field to store result of computation
 * @param type field to store type specification based on operation
 * @return int64_t 
 */
int64_t execute_equation(void *equation, uint64_t *result, uint64_t *type){
    // Cast 17-byte data to uint64_t
    uint64_t *raw = (uint64_t *) equation;
    // Extract parameters from raw 
    uint64_t num1 = raw[0];
    uint64_t operation = *((uint8_t *) equation + 8);
    uint64_t num2 = raw[1];

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
            return 1;
    }

    return 0;
}

