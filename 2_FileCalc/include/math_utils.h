// include/math_utils.h
// This header file declares common math functions

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Typedefs for prototypes
#include <stdint.h>

// Function declarations

int64_t add(int64_t a, int64_t b, int64_t* error);
int64_t subtract(int64_t a, int64_t b, int64_t* error);
int64_t multiply(int64_t a, int64_t b, int64_t* error);
int64_t divide(int64_t a, int64_t b, int64_t* error);
int64_t modulo(int64_t a, int64_t b, int64_t* error);
uint64_t shift_left(uint64_t a, uint64_t b, int64_t* error);
uint64_t shift_right(uint64_t a, uint64_t b, int64_t* error);
uint64_t bitwise_and(uint64_t a, uint64_t b, int64_t* error);
uint64_t bitwise_or(uint64_t a, uint64_t b, int64_t* error);
uint64_t bitwise_xor(uint64_t a, uint64_t b, int64_t* error);
uint64_t rotate_left(uint64_t a, uint64_t b, int64_t* error);
uint64_t rotate_right(uint64_t a, uint64_t b, int64_t* error);

#endif // MATH_UTILS_H
