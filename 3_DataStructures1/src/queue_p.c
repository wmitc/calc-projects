/**
 * @file queue_p.c
 * @author William Mitchell (william.b.mitchell46.mil@army.mil)
 * @brief Implementation of a priority queue
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

#ifndef DEBUG
#define DEBUG 0
#else
#define DEBUG 1
#endif

/**
 * @brief Implementation of the queue_p_init function
 */
queue_p_t *queue_p_init(uint32_t capacity, FREE_F customfree)
{
    // Check capacity
    if (capacity == 0)
    {
        fprintf(stderr, "[-] queue_init fail; capacity >= 1 required.\n");
        return NULL;
    }
    // Check customfree function
    if (!customfree)
    {
        fprintf(stderr, "[-] queue_init fail; customfree does not exist.\n");
        return NULL;
    }

    // Allocate the queue via malloc
    queue_p_t *queue = (queue_p_t *)malloc(sizeof(queue_p_t));

    // Check for error
    if (!queue)
    {
        fprintf(stderr, "[-] queue_p_init fail; malloc failure.\n");
        return NULL;
    }

    // Set parameters
    queue->arr = (queue_p_node_t **)calloc(capacity, sizeof(queue_p_node_t *));

    if (!queue->arr)
    {
        fprintf(stderr, "[-] queue_init fail; array allocation failed.\n");
        free(queue);
        return NULL;
    }
    // Set parameters
    queue->capacity   = capacity;
    queue->currentsz  = 0;
    queue->customfree = customfree;

    return queue;
}

/**
 * @brief Implementation of the queue_p_fullcheck function
 */
int queue_p_fullcheck(queue_p_t *queue)
{
    // Validate queue existence
    if (!queue)
    {
        fprintf(stderr, "[-] queue_p_fullcheck queue invalid fail.\n");
        return -1;
    }
    // Check whether queue is at capacity
    if (queue->currentsz == queue->capacity)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the queue_p_emptycheck function
 */
int queue_p_emptycheck(queue_p_t *queue)
{
    // Validate queue existence
    if (!queue)
    {
        fprintf(stderr, "[-] queue_emptycheck queue invalid fail.\n");
        return -1;
    }
    // Check whether queue is empty
    if (queue->currentsz == 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the queue_p_enqueue function
 */
int queue_p_enqueue(queue_p_t *queue, void *data, int priority)
{
    // Validate queue, data, and space for data
    if (!queue || !data || queue_p_fullcheck(queue))
    {
        fprintf(stderr, "[-] queue_enqueue queue invalid fail.\n");
        return 1;
    }
    // Instantiate a new node
    queue_p_node_t *new_node = (queue_p_node_t *)malloc(sizeof(queue_p_node_t));
    // Validate node
    if (!new_node)
    {
        fprintf(stderr, "[-] queue_enqueue node instantiation fail.\n");
        free(new_node);
        return 1;
    }

    // Set new_node->data
    new_node->data = data;
    // Set new_node->priority
    new_node->priority = priority;

    // Find correct location to insert data
    int i = 0;
    // Move index to point to first element of lower priority
    while (i < queue->currentsz && queue->arr[i]->priority >= priority)
    {
        i++;
    }
    // Move lower priority elements down one position
    for (int j = queue->currentsz; j > i; j--)
    {
        queue->arr[j] = queue->arr[j - 1];
    }
    // Emplace new element at index i
    queue->arr[i] = new_node;

    // Increment currentsz
    queue->currentsz++;

    return 0;
}

/**
 * @brief Implementation of the queue_p_dequeue function
 */
queue_p_node_t *queue_p_dequeue(queue_p_t *queue)
{
    // Validate queue exists and not empty
    if (!queue || queue_p_emptycheck(queue))
    {
        fprintf(stderr, "[-] queue_dequeue queue invalid fail.\n");
        return NULL;
    }
    // Get node from front of queue (has highest priority)
    queue_p_node_t *first_node = queue->arr[0];

    // Validate node
    if (!first_node)
    {
        fprintf(stderr, "[-] queue_dequeue first node failure.\n");
        return NULL;
    }

    // Shift all nodes
    for (uint32_t i = 0; i < queue->currentsz - 1; i++)
    {
        queue->arr[i] = queue->arr[i + 1];
    }
    // NULL out prior last element
    queue->arr[queue->currentsz - 1] = NULL;
    // Decrement current size
    queue->currentsz--;

    return first_node;
}

/**
 * @brief Implementation of the queue_p_peek function
 */
queue_p_node_t *queue_p_peek(queue_p_t *queue)
{
    // Validate queue exists and is not empty
    if (!queue || queue_p_emptycheck(queue))
    {
        fprintf(stderr, "[-] queue_peek queue invalid fail.\n");
        return NULL;
    }

    // Validate first node is not NULL
    if (!queue->arr[0])
    {
        fprintf(stderr, "[-] queue_peek first node is NULL fail.\n");
        return NULL;
    }

    // Return data from first element of queue
    return queue->arr[0];
}

/**
 * @brief Implementation of the queue_p_clear function
 */
int queue_p_clear(queue_p_t *queue)
{
    // Validate queue exists and is not empty
    if (!queue)
    {
        fprintf(stderr, "[-] queue_clear queue invalid fail.\n");
        return 1;
    }

    for (uint32_t i = 0; i < queue->currentsz; i++)
    {
        // Use customfree on node data if it exists
        if (queue->arr[i])
        {
            // Free the node with customfree
            queue->customfree(queue->arr[i]);
            // Set queue->arr[i] to NULL to prevent dangling pointer
            queue->arr[i] = NULL;
        }
    }

    // Zero out queue currentsz
    queue->currentsz = 0;

    return 0;
}

/**
 * @brief Implementation of the queue_p_destroy function
 */
int queue_p_destroy(queue_p_t **queue)
{
    // Validate queue exists and is not empty
    if (!queue || !(*queue))
    {
        fprintf(stderr, "[-] queue_destroy queue invalid fail.\n");
        return 1;
    }

    // Instantiate queue based on pointer to queue
    queue_p_t *queue_p = *queue;

    // Clear the queue
    queue_p_clear(queue_p);

    // Free structures
    free(queue_p->arr);
    free(queue_p);

    // Zero out pointer to prevent dangling pointer
    *queue = NULL;

    return 0;
}

/**
 * @brief Implementation of the custom_free function
 */
void custom_free(void *mem_addr)
{
    if (mem_addr)
    {
        free(mem_addr);
    }
}

int main()
{
    // Manual validation
    if (DEBUG)
    {
        // Example usage
        queue_p_t *queue = queue_p_init(5, custom_free);
        printf("initialized!\n");

        // Add some elements to the queue
        queue_p_enqueue(queue, 1, 2);
        queue_p_enqueue(queue, 2, 1);
        queue_p_enqueue(queue, 3, 4);
        queue_p_enqueue(queue, 4, 3);

        // Now print the conents of the queue
        for (int i = 0; i < queue->currentsz; i++)
        {
            printf("Node %d has data %d and priority %d\n",
                   i,
                   queue->arr[i]->data,
                   queue->arr[i]->priority);
        }

        // Now dequeue
        queue_p_node_t *node = queue_p_dequeue(queue);
        if (node)
        {
            queue->customfree(node);
        }
        printf("dequeued one item!\n");
        // Now print again
        for (int i = 0; i < queue->currentsz; i++)
        {
            printf("Node %d has data %d and priority %d\n",
                   i,
                   queue->arr[i]->data,
                   queue->arr[i]->priority);
        }

        // Clear queue
        queue_p_clear(queue);

        printf("cleared!\n");
        // Now print again
        for (int i = 0; i < queue->currentsz; i++)
        {
            printf("Node %d has data %d and priority %d\n",
                   i,
                   queue->arr[i]->data,
                   queue->arr[i]->priority);
        }
        queue_p_destroy(&queue);
        printf("destroyed!\n");

        free(queue);
    }

    return 0;
}