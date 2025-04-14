// src/math_utils.c
// This file implements simple math functions

#include <stdio.h>
#include <stdint.h>
#include "math_utils.h"

#define MAX_BITS 32

// Performs addition operation
int32_t add(int32_t a, int32_t b){
    if(a + b > INT32_MAX){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    }
	return a + b;
}

// Performs subraction operation
int32_t subtract(int32_t a, int32_t b){
    if(a - b < INT32_MIN){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    }
	return a - b;
}

// Performs multiplication operation
int32_t multiply(int32_t a, int32_t b){
    int64_t temp = (int64_t) a * (int64_t) b;
    if(temp > INT32_MAX || temp < INT32_MIN){
        fprintf(stderr, "[-] Integer overflow detected!\n");
        return -1;
    } 
	return a * b;
}

// Performs divide operation
int32_t divide(int32_t a, int32_t b){
    if(b == 0){
        fprintf(stderr, "[-] Divide by zero error!");
        return -1;
    }
    return a / b;
}

// Performs modulo operation
int32_t modulo(int32_t a, int32_t b){
    if(b == 0){
        fprintf(stderr, "[-] Divide by zero error!");
        return -1;
    }
    return a % b;
}

// Performs left shift operation
int32_t shift_left(int32_t a, int32_t b){
    printf("%d\n", a);
    if(b < 0 || b >= 32){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a << b;
}

// Performs right shift operation
int32_t shift_right(int32_t a, int32_t b){
    if(b < 0 || b >= 32){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a >> b;
}

// Performs bitwise AND operation
int32_t bitwise_and(int32_t a, int32_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a & b;
}

// Performs bitwise OR operation
int32_t bitwise_or(int32_t a, int32_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a | b;
}

// Performs bitwise XOR operation
int32_t bitwise_xor(int32_t a, int32_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    return a ^ b;
}

// Performs bitwise left rotation operation
int32_t rotate_left(int32_t a, int32_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    } 
    // Ensure b is in range
    b %= MAX_BITS;
    
    return ((a << b) | (a >> (MAX_BITS - b)));
}

// Performs bitwise right rotation operation
int32_t rotate_right(int32_t a, int32_t b){
    if(a < 0 || b < 0){
        fprintf(stderr, "[-] Bad input!");
        return -1;       
    }
    // Ensure b is in range
    b %= MAX_BITS;

    return ((a >> b) | (a << (MAX_BITS - b)));
}
