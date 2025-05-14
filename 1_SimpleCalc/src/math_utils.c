// src/math_utils.c
// This file implements simple math functions

#include <stdint.h>
#include <stdio.h>
#include "math_utils.h"

#define MAX_BITS 32

// Performs addition operation
int32_t add(int32_t a, int32_t b, int32_t* error)
{
    // Safe bounds check
    if ((b > 0 && a > INT32_MAX - b) || (b < 0 && a < INT32_MIN - b))
    {
        fprintf(stderr, "[-] Integer overflow detected in addition!\n");
        *error = 1;
        return 1;
    }
    return a + b;
}

// Performs subraction operation
int32_t subtract(int32_t a, int32_t b, int32_t* error)
{
    // Safe bounds check
    if ((b > 0 && a < INT32_MIN + b) || (b < 0 && a > INT32_MAX + b))
    {
        fprintf(stderr, "[-] Integer overflow detected in subtraction!\n");
        *error = 1;
        return 1;
    }
    return a - b;
}

// Performs multiplication operation
int32_t multiply(int32_t a, int32_t b, int32_t* error)
{
    int64_t temp = (int64_t) a * (int64_t) b;
    if (temp > INT32_MAX || temp < INT32_MIN)
    {
        fprintf(stderr, "[-] Integer overflow detected!\n");
        *error = 1;
        return 1;
    }
    return a * b;
}

// Performs divide operation
int32_t divide(int32_t a, int32_t b, int32_t* error)
{
    // Check divide by zero
    if (b == 0)
    {
        fprintf(stderr, "[-] Divide by zero error!\n");
        *error = 1;
        return 1;
    }
    // Check integer overflow
    if (a == INT32_MIN && b == -1)
    {
        if (b == 0)
        {
            fprintf(stderr, "[-] Integer overflow (INT_MIN / -1)!\n");
            *error = 1;
            return 1;
        }
    }
    return a / b;
}

// Performs modulo operation
int32_t modulo(int32_t a, int32_t b, int32_t* error)
{
    // Check modulo by zero
    if (b == 0)
    {
        fprintf(stderr, "[-] Modulo by zero error!");
        *error = 1;
        return 1;
    }
    // Check integer overflow
    if (a == INT32_MIN && b == -1)
    {
        if (b == 0)
        {
            fprintf(stderr, "[-] Modulo overflow (INT_MIN / -1)!\n");
            *error = 1;
            return 1;
        }
    }

    return a % b;
}

// Performs left shift operation
uint32_t shift_left(uint32_t a, uint32_t b, int32_t* error)
{
    if (b >= MAX_BITS)
    {
        fprintf(stderr, "[-] Shift amount out of range (0-31)!");
        *error = 1;
        return 1;
    }
    return a << b;
}

// Performs right shift operation
uint32_t shift_right(uint32_t a, uint32_t b, int32_t* error)
{
    if (b >= MAX_BITS)
    {
        fprintf(stderr, "[-] Shift amount out of range!");
        *error = 1;
        return 1;
    }
    return a >> b;
}

// Performs bitwise AND operation
uint32_t bitwise_and(uint32_t a, uint32_t b, int32_t* error)
{
    // No additional error checking required
    *error = 0;
    return a & b;
}

// Performs bitwise OR operation
uint32_t bitwise_or(uint32_t a, uint32_t b, int32_t* error)
{
    // No additional error checking required
    *error = 0;
    return a | b;
}

// Performs bitwise XOR operation
uint32_t bitwise_xor(uint32_t a, uint32_t b, int32_t* error)
{
    // No additional error checking required
    *error = 0;
    return a ^ b;
}

// Performs bitwise left rotation operation
uint32_t rotate_left(uint32_t a, uint32_t b, int32_t* error)
{
    // Ensure b is in range
    b %= MAX_BITS;
    // No additional error checking required
    *error = 0;

    return ((a << b) | (a >> (MAX_BITS - b)));
}

// Performs bitwise right rotation operation
uint32_t rotate_right(uint32_t a, uint32_t b, int32_t* error)
{
    // Ensure b is in range
    b %= MAX_BITS;
    // No additional error checking required
    *error = 0;

    return ((a >> b) | (a << (MAX_BITS - b)));
}
/*** end of file ***/
