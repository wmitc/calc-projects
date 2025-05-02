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
#include <string.h>
#include "hash_table.h"

/**
 * @brief Implementation of the hash_table_init function
  */
hash_table_t * hash_table_init(uint32_t size, FREE_F customfree)
{
    // Check capacity
    if(size == 0)
    {
        fprintf(stderr, "[-] hash_table_init fail; size >= 1 required.\n");
        return NULL;
    }
    // Check customfree function
    /*if(!customfree)
    {
        fprintf(stderr, "[-] hash_table_init fail; customfree does not exist.\n");
        return NULL;
    }*/

    // Allocate the queue via malloc
    hash_table_t *hash_table = (hash_table_t *) malloc(sizeof(hash_table_t));

    // Check for error 
    if(!hash_table)
    {
        fprintf(stderr, "[-] hash_table_init fail; malloc failure.\n");
        return NULL;
    }

    // Set parameters
    hash_table->table = (node_t **) calloc(size, sizeof(node_t *));

    if(!hash_table->table)
    {
        fprintf(stderr, "[-] queue_init fail; array allocation failed.\n");
        free(hash_table);
        return NULL;
    }

    hash_table->size = size;
    hash_table->customfree = customfree;

    return hash_table;
}

/**
 * @brief Basic dbj2 hash algorithm from:
 *        https://theartincode.stanis.me/008-djb2/
 * 
 * @param str Input string
 * @return unsigned long Hash value
 */
unsigned long hash(unsigned char *str, uint32_t size)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    // Return hash % size so that value is less than SIZE constant
    return hash % size;
}

/**
 * @brief Implementation of the hash_table_add function
 */
int hash_table_add(hash_table_t * table, void * data, char * key)
{
    // Validate table, data, and key exist
    if(!table || !data || !key)
    {
        fprintf(stderr, "[-] hash_table_add table invalid fail.\n");
        return 1;        
    }

    // Pull table index based on key
    int index = hash(key, table->size);
    node_t *new_node = malloc(sizeof(node_t)); 
    // Validate node
    if(!new_node)
    {
        fprintf(stderr, "[-] hash_table_add node instantiation fail.\n");
        return 1;          
    }        
    
    // Copy key
    new_node->key = strdup(key);

    // Validate key copy
    if(!new_node->key)
    {
        fprintf(stderr, "[-] hash_table_add key copy fail.\n");
        free(new_node);
        return 1;              
    }
    
    // Set other parameters
    new_node->data = data;
    new_node->next = NULL;

    // Insert new_node into table
    if(!table->table[index])
    {
        // new_node is first node in <index> row
        table->table[index] = new_node;
    }
    else
    {
        // new_node is NOT first node in <index> row
        node_t *curr = table->table[index];
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = new_node;
    }

    return 0;
}

/**
 * @brief Implementation of the hash_table_lookup function
 */
void * hash_table_lookup(hash_table_t * table, char * key)
{
    // Validate table, data, and key exist
    if(!table || !key)
    {
        fprintf(stderr, "[-] hash_table_lookup table invalid fail.\n");
        return NULL;        
    }

    // Pull the index based on the key
    uint32_t index = hash((unsigned char *)key, table->size);
    // Get first node in <index> row
    node_t *curr = table->table[index];

    // Find data of element corresponding to <key>
    while(curr != NULL)
    {
        if(strcmp(curr->key, key) == 0)
        {
            return curr->data;
        }
        curr = curr->next;
    }

    return NULL;
}

/**
 * @brief Implementation of the hash_table_remove function
 */
int hash_table_remove(hash_table_t * table, char * key)
{
    // Validate table, data, and key exist
    if(!table || !key)
    {
        fprintf(stderr, "[-] hash_table_add table invalid fail.\n");
        return 1;        
    }

    // Pull the index based on the key
    int index = hash(key, table->size);
    // Get first node in <index> row
    node_t *curr = table->table[index];
    node_t *prev = NULL;

    // Find data of element corresponding to <key>
    while(curr != NULL)
    {
        if(strcmp(curr->key, key) == 0)
        {
            // Check if first item is removal target
            if(!prev)
            {
                // Shift start forward one spot
                table->table[index] = curr->next;
            }
            else
            {
                // Otherwise move prev's next to curr's next
                prev->next = curr->next;
            }
            
            // Free data with customfree
            if(table->customfree)
            {
                table->customfree(curr->data);
            }
            free(curr->key);
            free(curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    return 1;    
}

/**
 * @brief Implementation of the hash_table_clear function
 */
int hash_table_clear(hash_table_t * table)
{
    // Validate hash_table exists and is not empty
    if(!table)
    {
        fprintf(stderr, "[-] hash_table_clear hash_table invalid fail.\n");
        return 1;        
    }
    
    // Iterate over table slots
    for(uint32_t i = 0; i < table->size; i++)
    {
        // Check if row has any nodes
        if(table->table[i])
        {
            // Free all nodes in row
            node_t *curr = table->table[i];
            while(curr != NULL){
                node_t *next = curr->next;

                // Use customfree on data
                if(table->customfree)
                {
                    table->customfree(curr->data);
                }
                // Free current's key and current itself
                free(curr->key);
                free(curr);
                // Move curr forward
                curr = next;
            }

            // Set row entry to NULL to avoid dangling pointer
            table->table[i] = NULL;
        }
    }

    // Zero out queue currentsz
    table->size = 0;

    return 0;
}

/**
 * @brief Implementation of the hash_table_destroy function
 */
int hash_table_destroy(hash_table_t ** table_addr)
{
    // Validate hash_table exists and is not empty
    if(!table_addr || !(*table_addr))
    {
        fprintf(stderr, "[-] hash_table_destroy hash_table invalid fail.\n");
        return 1;        
    }

    // Instantiate hash_table based on pointer to hash_table
    hash_table_t *hash_table = *table_addr;

    // Clear the hash_table
    hash_table_clear(hash_table);

    // Free
    free(hash_table->table);
    free(hash_table);

    // Zero out pointer to prevent dangling pointer
    *table_addr = NULL;

    return 0;
}

/**
 * @brief Implementation of the custom_free function
 */
void custom_free(void * mem_addr)
{
    if(mem_addr)
    {
        free(mem_addr);
    }

}

int main()
{
    printf("hello world\n");
    return 0;
}