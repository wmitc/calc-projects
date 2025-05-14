// src/math_utils.c
// This file implements simple math functions

#include <stdio.h>
#include <stdint.h>
#include "math_utils.h"

#define MAX_BITS 64

/**
 * @brief Perform addition operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
int64_t add(int64_t a, int64_t b, int64_t* error)
{
    if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b))
    {
        fprintf(stderr, "[-] Integer overflow detected in addition!\n");
        *error = 1;
        return 1;
    }
    *error = 0;

    return a + b;
}

/**
 * @brief Perform subtraction operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
int64_t subtract(int64_t a, int64_t b, int64_t* error)
{
    if ((b > 0 && a < INT64_MIN + b) || (b < 0 && a > INT64_MAX + b))
    {
        fprintf(stderr, "[-] Integer overflow detected in subtraction!\n");
        *error = 1;
        return 1;
    }
    *error = 0;

    return a - b;
}

/**
 * @brief Perform multiplication operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
int64_t multiply(int64_t a, int64_t b, int64_t* error)
{
    // Error checking for multiplication
    if (a > 0)
    {
        if (b > 0)
        {
            if (a > INT64_MAX / b)
            {
                *error = 1;
            }
        }
        else if (b < 0)
        {
            if (b < INT64_MIN / a)
            {
                *error = 1;
            }
        }
    }
    else if (a < 0)
    {
        if (b > 0)
        {
            if (a < INT64_MIN / b)
            {
                *error = 1;
            }
        }
        else if (b < 0)
        {
            if (a < INT64_MAX / b)
            {
                *error = 1;
            }
        }
    }
    if (*error)
    {
        fprintf(stderr, "[-] Integer overflow detected in multiplication!\n");
        return 1;
    }
    return a * b;
}

/**
 * @brief Perform division operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
int64_t divide(int64_t a, int64_t b, int64_t* error)
{
    if (b == 0)
    {
        fprintf(stderr, "[-] Divide by zero error!");
        *error = 1;
        return 1;
    }
    // Check integer overflow
    if (a == INT32_MIN && b == -1)
    {
        fprintf(stderr, "[-] Integer overflow (INT_MIN / -1)!");
        *error = 1;
        return 1;
    }
    return a / b;
}

/**
 * @brief Perform modulo operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
int64_t modulo(int64_t a, int64_t b, int64_t* error)
{
    if (b == 0)
    {
        fprintf(stderr, "[-] Modulo by zero error!");
        *error = 1;
        return 1;
    }
    // Check integer overflow
    if (a == INT32_MIN && b == -1)
    {
        fprintf(stderr, "[-] Modulo overflow (INT_MIN / -1)!");
        *error = 1;
        return 1;
    }
    return a % b;
}

/**
 * @brief Perform left shift operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t shift_left(uint64_t a, uint64_t b, int64_t* error)
{
    if (b >= MAX_BITS)
    {
        fprintf(stderr, "[-] Bad input!");
        *error = 1;
        return 1;
    }
    return a << b;
}

/**
 * @brief Perform right shift operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t shift_right(uint64_t a, uint64_t b, int64_t* error)
{
    if (b >= MAX_BITS)
    {
        fprintf(stderr, "[-] Bad input!");
        *error = 1;
        return 1;
    }
    return a >> b;
}

/**
 * @brief Perform bitwise AND operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t bitwise_and(uint64_t a, uint64_t b, int64_t* error)
{
    // No additional error checking required
    *error = 0;
    return a & b;
}

/**
 * @brief Perform bitwise OR operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t bitwise_or(uint64_t a, uint64_t b, int64_t* error)
{
    // No additional error checking required
    *error = 0;
    return a | b;
}

/**
 * @brief Perform bitwise XOR operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t bitwise_xor(uint64_t a, uint64_t b, int64_t* error)
{
    // No additional error checking required
    *error = 0;
    return a ^ b;
}

/**
 * @brief Perform left rotate operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t rotate_left(uint64_t a, uint64_t b, int64_t* error)
{
    // Ensure b is in range
    b %= MAX_BITS;
    // No additional error checking required
    *error = 0;

    return ((a << b) | (a >> (MAX_BITS - b)));
}

/**
 * @brief Perform right rotate operation
 *
 * @param a First parameter
 * @param b Second parameter
 * @param error Error flag
 * @return int64_t Solution
 */
uint64_t rotate_right(uint64_t a, uint64_t b, int64_t* error)
{
    // Ensure b is in range
    b %= MAX_BITS;
    // No additional error checking required
    *error = 0;

    return ((a >> b) | (a << (MAX_BITS - b)));
}
/*** end of file ***/
