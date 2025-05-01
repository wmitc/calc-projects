/**
 * @file stack.c
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
#include "stack.h"

/**
 * @brief Implementation of the stack_init function
 */
stack_t * stack_init(uint32_t capacity, FREE_F customfree)
{
    // Check capacity
    if(capacity == 0)
    {
        fprintf(stderr, "[-] stack_init fail; capacity >= 1 required.\n");
        return NULL;
    }
    // Check customfree function
    if(!customfree)
    {
        fprintf(stderr, "[-] stack_init fail; customfree does not exist.\n");
        return NULL;
    }
    
    // Allocate the stack via malloc
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    
    // Check for error
    if(!stack)
    {
        fprintf(stderr, "[-] stack_init fail; malloc failure.\n");
        return NULL;
    }
    
    // Set parameters
    stack->arr = (stack_node_t **) calloc(capacity, sizeof(stack_node_t *));
    
    if (!stack->arr)
    {
        fprintf(stderr, "[-] stack_init fail; array allocation failed.\n");
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->currentsz = 0;
    stack->customfree = customfree;

    return stack;
}

/**
 * @brief Implementation of the stack_fullcheck function
 */
int stack_fullcheck(stack_t * stack)
{
    // Validate stack existence
    if(!stack)
    {
        fprintf(stderr, "[-] stack_fullcheck stack invalid fail.\n");
        return 1;
    }
    // Check whether stack is at capacity
    if(stack->currentsz == stack->capacity)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the empty_check function
 */
int stack_emptycheck(stack_t * stack)
{
    // Validate stack existence
    if(!stack)
    {
        fprintf(stderr, "[-] stack_emptycheck stack invalid fail.\n");
        return 1;
    }
    // Check whether stack is at empty
    if(stack->currentsz == 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the stack_push function
 */
int stack_push(stack_t * stack, void * data)
{
    // Validate stack, data, and space for data
    if (!stack || !data || stack_fullcheck(stack)) 
    {
        fprintf(stderr, "[-] stack_push stack invalid fail.\n");
        return 1;
    }
    // Instantiate a new node
    stack_node_t *new_node = (stack_node_t *) malloc(sizeof(stack_node_t));
    // Validate node
    if (!new_node)
    {
        fprintf(stderr, "[-] stack_push node instantiation fail.\n");
        return 1;        
    }
    // Set new_node->data and emplace on stack
    new_node->data = data;
    //memcpy(new_node->data, data, sizeof(data));
    stack->arr[stack->currentsz] = new_node;
    // Increment currentsz
    stack->currentsz++;

    return 0;
}

/**
 * @brief Implementation of the stack_pop function
 */
stack_node_t * stack_pop(stack_t * stack)
{
    // Validate stack existence; confirm stack is non-empty
    if(!stack || stack_emptycheck(stack))
    {
        fprintf(stderr, "[-] stack_pop stack invalid fail.\n");
        return 1;
    }

    // Remove node from the top of the stack
    stack->currentsz--;
    stack_node_t *node = stack->arr[stack->currentsz];
    stack->arr[stack->currentsz] = NULL;

    return node;
}

/**
 * @brief Implementation of the stack_peek function
 */
stack_node_t * stack_peek(stack_t * stack)
{
    // Validate stack existence; confirm stack is non-empty
    if(!stack || stack_emptycheck(stack))
    {
        fprintf(stderr, "[-] stack_peek stack invalid fail.\n");
        return 1;
    }

    // Get value at top of stack
    return stack->arr[stack->currentsz - 1];
}

/**
 * @brief Implementation of the stack_clear function
 */
int stack_clear(stack_t * stack)
{
    // Validate stack existence
    if(!stack)
    {
        fprintf(stderr, "[-] stack_clear stack invalid fail.\n");
        return 1;
    }

    // Iterate over the array, freeing all data
    for(int i = 0; i < stack->currentsz; i++)
    {
        // Free data if the stack node exists
        if(stack->arr[i])
        {
            /*if(stack->arr[i]->data)
            {
                stack->customfree(stack->arr[i]->data);
            }*/
            // Free the stack node
            free(stack->arr[i]);
            // Prevent dangling pointer
            stack->arr[i] = NULL;           
        }

    }

    // Zero out stack currentsz
    stack->currentsz = 0;

    return 0;
}

/**
 * @brief Implementation of the stack_destroy function
 */
int stack_destroy(stack_t ** stack)
{
    // Validate stack existence
    if(!stack || !*stack)
    {
        fprintf(stderr, "[-] stack_clear stack invalid fail.\n");
        return 1;
    }
    // Clear the stack
    stack_clear(*stack);
    // Free the allocated stack array
    free((*stack)->arr);
    // Free the stack
    free(*stack);
    // Set stack pointer to NULL to prevent dangling pointer
    *stack = NULL;

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
    printf("test\n");
    stack_t *stack = stack_init(5, custom_free);
    printf("initialized!\n");

    // Add some elements to the queue
    stack_push(stack,1);
    stack_push(stack,2);
    stack_push(stack,3);;
    stack_push(stack,4);

    // Now print the conents of the queue
    for(int i = 0; i < stack->currentsz; i++)
    {
        printf("Node %d has data %d\n",i,stack->arr[i]->data);
    }


    stack_pop(stack);
    printf("\nTop node popped!\n");
    // Top node popped
    for(int i = 0; i < stack->currentsz; i++)
    {
        printf("Node %d has data %d\n",i,stack->arr[i]->data);
    }




    stack_pop(stack);
    printf("\nTop node popped!\n");


    //queue_p_clear(queue);    
    
    //printf("cleared!\n");
    // Now print again
    for(int i = 0; i < stack->currentsz; i++)
    {
        printf("Node %d has data %d\n",i,stack->arr[i]->data);
    }

    stack_clear(stack);    
    
    printf("cleared!\n");
    for(int i = 0; i < stack->currentsz; i++)
    {
        printf("Node %d has data %d\n",i,stack->arr[i]->data);
    }   
    stack_destroy(&stack);
    printf("destroyed!\n");

    return 0;
}