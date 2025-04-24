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
    queue_t *t;
    return t;
}

/**
 * @brief Implementation of the queue_fullcheck function
 */
int queue_fullcheck(queue_t * queue)
{
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
    return 0;
}

/**
 * @brief Implementation of the queue_enqueue function
 */
int queue_enqueue(queue_t * queue, void * data)
{
    return 0;
}

/**
 * @brief Implementation of the queue_dequeue function
 */
queue_node_t * queue_dequeue(queue_t * queue)
{
    queue_node_t *t;
    return t;
}

/**
 * @brief Implementation of the queue_peek function
 */
queue_node_t * queue_peek(queue_t * queue)
{
    queue_node_t *t;
    return t;
}

/**
 * @brief Implementation of the queue_clear function
 */
int queue_clear(queue_t * queue)
{
    return 0;
}

/**
 * @brief Implementation of the queue_destroy function
 */
int queue_destroy(queue_t ** queue_addr)
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