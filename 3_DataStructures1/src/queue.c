/**
 * @file queue.c
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
#include "queue.h"

/**
 * @brief Implementation of the queue_init function
 */
queue_t * queue_init(uint32_t capacity, FREE_F customfree)
{
    // Check capacity
    if(capacity <= 0)
    {
        fprintf(stderr, "[-] queue_init fail; capacity >= 1 required.\n");
        return NULL;
    }
    // Check customfree function
    if(!customfree)
    {
        fprintf(stderr, "[-] queue_init fail; customfree does not exist.\n");
        return NULL;
    }

    // Allocate the queue via malloc
    queue_t *queue = (queue_t *) malloc(sizeof(queue_t));

    // Check for error 
    if(!queue)
    {
        fprintf(stderr, "[-] queue_init fail; malloc failure.\n");
        return NULL;
    }

    // Set parameters
    queue->arr = (queue_node_t **) calloc(capacity, sizeof(queue_node_t *));
    
    if(!queue->arr)
    {
        fprintf(stderr, "[-] queue_init fail; array allocation failed.\n");
        free(queue);
        return NULL;
    }

    queue->capacity = capacity;
    queue->currentsz = 0;
    queue->customfree = customfree;
}

/**
 * @brief Implementation of the queue_fullcheck function
 */
int queue_fullcheck(queue_t * queue)
{
    // Validate queue existence
    if(!queue){
        fprintf(stderr, "[-] queue_fullcheck queue invalid fail.\n");
        return -1;        
    }
    // Check whether queue is at capacity
    if(queue->currentsz == queue->capacity)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief verifies that queue isn't empty
 *
 * @param queue pointer queue object
 * @return 0 on success, non-zero value on failure
 */
int queue_emptycheck(queue_t * queue)
{
    // Validate queue existence
    if(!queue){
        fprintf(stderr, "[-] queue_emptycheck queue invalid fail.\n");
        return -1;        
    }
    // Check whether queue is empty
    if(queue->currentsz == 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the queue_enqueue function
 */
int queue_enqueue(queue_t * queue, void * data)
{
    // Validate queue, data, and space for data
    if(!queue || !data || queue_fullcheck(queue))
    {
        fprintf(stderr, "[-] queue_enqueue queue invalid fail.\n");
        return 1;        
    }    
    // Instantiate a new node
    queue_node_t *new_node = (queue_node_t *) malloc(sizeof(queue_node_t));
    if(!new_node)
    {
        fprintf(stderr, "[-] queue_enqueue node instantiation fail.\n");
        return 1;          
    }
    // Assign data to the node
    new_node->data = data;
    queue->arr[queue->currentsz] = new_node;
    
    queue->currentsz++;

    return 0;
}

/**
 * @brief Implementation of the queue_dequeue function
 */
queue_node_t * queue_dequeue(queue_t * queue)
{
    // Validate queue exists and not empty
    if(!queue || queue_emptycheck(queue))
    {
        fprintf(stderr, "[-] queue_dequeue queue invalid fail.\n");
        return NULL;        
    }    
    // Get node from front of queue
    queue_node_t *first_node = queue->arr[0];

    // Validate node
    if(!first_node)
    {
        fprintf(stderr, "[-] queue_dequeue first node failure.\n");
        return NULL;              
    }

    // Shift all nodes
    for(uint32_t i = 0; i < queue->currentsz - 1; i++)
    {
        queue->arr[i] = queue->arr[i + 1]; 
    }
    queue->arr[queue->currentsz - 1] = NULL;
    
    queue->currentsz--;

    return first_node;
}

/**
 * @brief Implementation of the queue_peek function
 */
queue_node_t * queue_peek(queue_t * queue)
{
    // Validate queue exists and is not empty
    if(!queue || queue_emptycheck(queue))
    {
        fprintf(stderr, "[-] queue_peek queue invalid fail.\n");
        return NULL;        
    }

    // Validate first node is not NULL
    if(!queue->arr[0])
    {
        fprintf(stderr, "[-] queue_peek first node is NULL fail.\n");
        return NULL;        
    }    
    
    // Return data from first element of queue
    return queue->arr[0];
}

/**
 * @brief Implementation of the queue_clear function
 */
int queue_clear(queue_t * queue)
{
    // Validate queue exists and is not empty
    if(!queue)
    {
        fprintf(stderr, "[-] queue_clear queue invalid fail.\n");
        return 1;        
    }
    //fprintf(stdout, "Size of currensz is: %d\n", queue->currentsz);
    for(uint32_t i = 0; i < queue->currentsz; i++)
    {
        // Use customfree on node data
        queue->arr[i]->data = 0;
        // Decrement the size of the queue for each node freed
        queue->currentsz--;
        //fprintf(stdout, "Size of currensz is: %d\n", queue->currentsz);
    }
    // Use free on queue itself
    //free(queue);
    //fprintf(stdout, "Size of currensz is: %d\n", queue->currentsz);

    // Zero out queue currentsz
    queue->currentsz = 0;

    return 0;
}

/**
 * @brief Implementation of the queue_destroy function
 */
int queue_destroy(queue_t ** queue_addr)
{
    // Validate queue exists and is not empty
    if(!queue_addr || !(*queue_addr))
    {
        fprintf(stderr, "[-] queue_destroy queue invalid fail.\n");
        return 1;        
    }

    // Instantiate queue based on pointer to queue
    queue_t *queue = *queue_addr;

    // Clear the queue
    clear_queue(queue_addr);

    // Free
    free(queue->arr);
    free(queue);

    // Zero out pointer to prevent dangling pointer
    *queue_addr = NULL;

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