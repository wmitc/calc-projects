// include/math_utils.h
// This header file declares common math functions

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Typedefs for prototypes
#include <stdint.h>

// Function declarations

int32_t add(int32_t a, int32_t b);
int32_t subtract(int32_t a, int32_t b);
int32_t multiply(int32_t a, int32_t b);
int32_t divide(int32_t a, int32_t b);
int32_t modulo(int32_t a, int32_t b);
int32_t shift_left(int32_t a, int32_t b);
int32_t shift_right(int32_t a, int32_t b);
int32_t bitwise_and(int32_t a, int32_t b);
int32_t bitwise_or(int32_t a, int32_t b);
int32_t bitwise_xor(int32_t a, int32_t b);
int32_t rotate_left(int32_t a, int32_t b);
int32_t rotate_right(int32_t a, int32_t b);

#endif // MATH_UTILS_H
