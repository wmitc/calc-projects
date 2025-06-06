#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdint.h>

int64_t evaluate_signed_equation(int64_t num1,
                                 int8_t operation,
                                 int64_t num2,
                                 int64_t *result,
                                 int8_t *type);
uint64_t evaluate_unsigned_equation(uint64_t num1,
                                    int8_t operation,
                                    uint64_t num2,
                                    uint64_t *result,
                                    int8_t *type);

#endif
