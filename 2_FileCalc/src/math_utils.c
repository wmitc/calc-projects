// src/math_utils.c
// This file implements simple math functions

#include <stdio.h>
#include <stdint.h>
#include "math_utils.h"

#define MAX_BITS 64

// Performs addition operation
int64_t add(int64_t a, int64_t b){
    if(a + b > INT64_MAX){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    }
	return a + b;
}

// Performs subraction operation
int64_t subtract(int64_t a, int64_t b){
    if(a - b < INT64_MIN){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    }
	return a - b;
}

// Performs multiplication operation
int64_t multiply(int64_t a, int64_t b){
    int64_t temp = (int64_t) a * (int64_t) b;
    if(temp > INT64_MAX || temp < INT64_MIN){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    } 
	return a * b;
}

// Performs divide operation
int64_t divide(int64_t a, int64_t b){
    if(b == 0){
        fprintf(stderr, "[-] Divide by zero error!");
        return -1;
    }
    return a / b;
}

// Performs modulo operation
int64_t modulo(int64_t a, int64_t b){
    if(b == 0){
        fprintf(stderr, "[-] Divide by zero error!");
        return -1;
    }
    return a % b;
}

// Performs left shift operation
uint64_t shift_left(uint64_t a, uint64_t b){
    printf("%d\n", a);
    if(b < 0 || b >= 32){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a << b;
}

// Performs right shift operation
uint64_t shift_right(uint64_t a, uint64_t b){
    if(b < 0 || b >= 32){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a >> b;
}

// Performs bitwise AND operation
uint64_t bitwise_and(uint64_t a, uint64_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a & b;
}

// Performs bitwise OR operation
uint64_t bitwise_or(uint64_t a, uint64_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a | b;
}

// Performs bitwise XOR operation
uint64_t bitwise_xor(uint64_t a, uint64_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a ^ b;
}

// Performs bitwise left rotation operation
uint64_t rotate_left(uint64_t a, uint64_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    } 
    // Ensure b is in range
    b %= MAX_BITS;
    
    return ((a << b) | (a >> (MAX_BITS - b)));
}

// Performs bitwise right rotation operation
uint64_t rotate_right(uint64_t a, uint64_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    // Ensure b is in range
    b %= MAX_BITS;

    return ((a >> b) | (a << (MAX_BITS - b)));
}
