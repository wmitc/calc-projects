/**
 * @file hash_table.c
 * @author William Mitchell (william.b.mitchell46.mil@army.mil)
 * @brief 
 * @version 0.1
 * @date 2025-04-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

/**
 * @brief Implementation of the hash_table_init function
  */
hash_table_t * hash_table_init(uint32_t size, FREE_F customfree)
{
    hash_table_t *t;
    return t;
}

/**
 * @brief Implementation of the hash_table_add function
 */
int hash_table_add(hash_table_t * table, void * data, char * key)
{
    return 0;
}

/**
 * @brief Implementation of the hash_table_lookup function
 */
void * hash_table_lookup(hash_table_t * table, char * key)
{
    
}

/**
 * @brief Implementation of the hash_table_remove function
 */
int hash_table_remove(hash_table_t * table, char * key)
{
    return 0;
}

/**
 * @brief Implementation of the hash_table_clear function
 */
int hash_table_clear(hash_table_t * table)
{
    return 0;
}

/**
 * @brief Implementation of the hash_table_destroy function
 */
int hash_table_destroy(hash_table_t ** table_addr)
{
    return 0;
}

/**
 * @brief Implementation of the custom_free function
 */
void custom_free(void * mem_addr)
{

    free(mem_addr);

}

int main()
{
    printf("hello world\n");
    return 0;
}