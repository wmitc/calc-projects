// include/math_utils.h
// This header file declares common math functions

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Typedefs for prototypes
#include <stdint.h>

// Function declarations

int32_t add(int32_t a, int32_t b, int32_t* error);
int32_t subtract(int32_t a, int32_t b, int32_t* error);
int32_t multiply(int32_t a, int32_t b, int32_t* error);
int32_t divide(int32_t a, int32_t b, int32_t* error);
int32_t modulo(int32_t a, int32_t b, int32_t* error);
uint32_t shift_left(uint32_t a, uint32_t b, int32_t* error);
uint32_t shift_right(uint32_t a, uint32_t b, int32_t* error);
uint32_t bitwise_and(uint32_t a, uint32_t b, int32_t* error);
uint32_t bitwise_or(uint32_t a, uint32_t b, int32_t* error);
uint32_t bitwise_xor(uint32_t a, uint32_t b, int32_t* error);
uint32_t rotate_left(uint32_t a, uint32_t b, int32_t* error);
uint32_t rotate_right(uint32_t a, uint32_t b, int32_t* error);

#endif // MATH_UTILS_H
