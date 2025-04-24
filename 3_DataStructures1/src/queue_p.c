/**
 * @file queue_p.c
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
#include "queue_p.h"

/**
 * @brief Implementation of the queue_p_init function
 */
queue_p_t * queue_p_init(uint32_t capacity, FREE_F customfree)
{
    queue_p_t *q;
    return q;
}

/**
 * @brief Implementation of the queue_p_fullcheck function
 */
int queue_p_fullcheck(queue_p_t * queue)
{
    return 0;
}

/**
 * @brief Implementation of the queue_p_emptycheck function
 */
int queue_p_emptycheck(queue_p_t * queue)
{
    return 0;
}

/**
 * @brief Implementation of the queue_p_enqueue function
 */
int queue_p_enqueue(queue_p_t * queue, void * data, int priority)
{
    return 0;
}

/**
 * @brief Implementation of the queue_p_dequeue function
 */
queue_p_node_t * queue_p_dequeue(queue_p_t * queue)
{
    queue_p_node_t *p;
    return p;
}

/**
 * @brief Implementation of the queue_p_peek function
 */
queue_p_node_t * queue_p_peek(queue_p_t * queue)
{
    queue_p_node_t *p;
    return p;
}

/**
 * @brief Implementation of the queue_p_clear function
 */
int queue_p_clear(queue_p_t * queue)
{
    return 0;
}

/**
 * @brief Implementation of the queue_p_destroy function
 */
int queue_p_destroy(queue_p_t ** queue)
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