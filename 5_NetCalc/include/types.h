// include/types.h
// Define structs for handling file specifications
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define NET_HDR_SZ 48
#define NET_NAME_FIELD_SZ 32

typedef struct
{
    uint32_t hdr_len;                     // 4 bytes
    uint32_t fname_len;                   // 4 bytes
    uint64_t pkt_len;                     // 8 bytes
    char filename[NET_NAME_FIELD_SZ + 1]; // 32 bytes + 1 for null-terminator
} __attribute__((packed)) net_header_t;

// File header
typedef struct
{
    int32_t magic_number;
    int64_t fileID;
    int64_t num_of_equations;
    int8_t flag;
    int32_t offset;
    int16_t num_of_opt_headers;
} __attribute__((packed)) file_header;

// Unsolved equation
typedef struct
{
    int32_t equationID;
    int8_t flag;
    int64_t operand1;
    int8_t operation;
    int64_t operand2;
    int8_t padding[10]; // padding to 32 bytes
} __attribute__((packed)) unsolved_equation;

// Solved equation
typedef struct
{
    int32_t equationID;
    int8_t flag;
    int8_t type;
    int64_t solution;
} __attribute__((packed)) solved_equation;

#endif
