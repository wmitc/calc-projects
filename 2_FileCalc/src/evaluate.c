#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "math_utils.h"
#include "evaluate.h"

// Enum to specify equation types, per FileSpec.pdf
typedef enum type_t_tag {
    INT64_T = 0x1,
    UINT64_T = 0x2
} type_t;

// Enum to specify operator codes, per FileSpec.pdf
typedef enum simplecalc_ops_tag {
    ADDITION = 0x1,
    SUBTRACTION = 0x2,
    MULTIPLICATION = 0x3,
    DIVISION = 0x4,
    MODULO = 0x5,
    SHIFTLEFT = 0x6,
    SHIFTRIGHT = 0x7,
    AND = 0x8,
    OR = 0x9,
    XOR = 0xa,
    ROTATELEFT = 0xb,
    ROTATERIGHT = 0xc
} simplecalc_ops;


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
int64_t evaluate_signed_equation(int64_t num1, int8_t operation, int64_t num2,
                                 int64_t* result, int8_t* type)
{
    
    // Create error parameter to track whether solving equation was successful/unsuccesful,
    // result will be recorded via a set bit when writing to output folder
    int64_t error = 0;
    // Set answer type
    type_t ans_type = INT64_T;
    // Set operation type
    simplecalc_ops op = operation;

    // Use switch to determine and perform operation
    switch (op)
    {
        case ADDITION:
            *result = add(num1, num2, &error);
            *type = ans_type;
            break;
        case SUBTRACTION:
            *result = subtract(num1, num2, &error);
            *type = ans_type;
            break;
        case MULTIPLICATION:
            *result = multiply(num1, num2, &error);
            *type = ans_type;
            break;
        case DIVISION:
            *result = divide(num1, num2, &error);
            *type = ans_type;
            break;
        case MODULO:
            *result = modulo(num1, num2, &error);
            *type = ans_type;
            break;
        default:
            fprintf(stderr, "[-] Invalid operation.");
            // Return 0 to indicate unsolved
            return 0;
    }

    // Return 1 to indicate equation was solved
    return 1;
}

/**
 * @brief Execute the specified operation on the user-supplied operands
 *
 * @param num1 First operand
 * @param operation Operator
 * @param num2 Second operand
 * @param result Field to store result of computation
 * @param type Field to store type specification based on operation
 * @return uint64_t Solved? True/False
 */
uint64_t evaluate_unsigned_equation(uint64_t num1, int8_t operation,
                                    uint64_t num2, uint64_t* result,
                                    int8_t* type)
{
    // Create error parameter to track whether solving equation was successful/unsuccesful,
    // result will be recorded via a set bit when writing to output folder
    int64_t error = 0;
    // Set answer type
    type_t ans_type = UINT64_T;
    // Set operation type
    simplecalc_ops op = operation;
    // Use switch to determine and perform operation
    switch (op)
    {
        case SHIFTLEFT:
            *result = shift_left(num1, num2, &error);
            *type = ans_type;
            break;
        case SHIFTRIGHT:
            *result = shift_right(num1, num2, &error);
            *type = ans_type;
            break;
        case AND:
            *result = bitwise_and(num1, num2, &error);
            *type = ans_type;
            break;
        case OR:
            *result = bitwise_or(num1, num2, &error);
            *type = ans_type;
            break;
        case XOR:
            *result = bitwise_xor(num1, num2, &error);
            *type = ans_type;
            break;
        case ROTATELEFT:
            *result = rotate_left(num1, num2, &error);
            *type = ans_type;
            break;
        case ROTATERIGHT:
            *result = rotate_right(num1, num2, &error);
            *type = ans_type;
            break;
        default:
            fprintf(stderr, "[-] Invalid operation.");
            // Return 0 to indicate unsolved
            return 0;
    }

    // Return 1 to indicate equation was solved
    return 1;
}
/*** end of file ***/
