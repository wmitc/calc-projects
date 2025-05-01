/**
 * @file linked_list.c
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
#include "linked_list.h"

#define HEAD_POSITION 1

/**
 * @brief Create a node object
 * 
 * @param data data for node to hold
 * @param position position relevant to head (1)
 * @return list_node_t* new node
 */
list_node_t *create_node(void * data, uint32_t position)
{
    list_node_t *node = malloc(sizeof(list_node_t));
    if(!node)
    {
        fprintf(stderr, "[-] New node instantiation failed.\n");
        return NULL;
    }
    
    // Assign node parameters
    node->data = data;
    node->next = NULL;
    node->position = position;

    return node;
}

/**
 * @brief Implementation of the default_compare function
 */
void * default_compare(void * value_to_find, void * node)
{
    if (value_to_find == node)
    {
        return node;
    }
    else
    {
        return NULL;
    }
}

/**
 * @brief Implementation of the list_new function
 */
list_t * list_new(FREE_F custom_free, CMP_F compare_function)
{
    // Allocate space for the list
    list_t *list = malloc(sizeof(list_t));
    // Validate list create was successful
    if(!list)
    {
        fprintf(stderr, "[-] Linked list creation failed.\n");
        return NULL;
    }
    // Set linked list parameters
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->customfree = custom_free;
    list->compare_function = compare_function;
    return list;
}

/**
 * @brief Implementation of the list_push_head function
 */
int list_push_head(list_t * list, void * data)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_push_tail.\n");
        return  -1;
    }
    // Create new node
    list_node_t *node = create_node(data, HEAD_POSITION);
    // Validate node existence
    if(!node)
    {
        fprintf(stderr, "[-] Node nonexistent in list_push_tail.\n");
        return  -1;
    }

    node->next = list->head;
    list->head = node;
    // Iterate over list, from head->next to end, incrementing position
    list_node_t *curr = list->head->next;
    uint32_t pos = HEAD_POSITION + 1;
    while(curr)
    {
        curr->position++;
        curr = curr->next;       
    }

    return 0;
}

/**
 * @brief Implementation of the list_push_tail function
 */
int list_push_tail(list_t * list, void * data)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_push_tail.\n");
        return  -1;
    }
    // Create new node
    list_node_t *node = create_node(data, list->size + 1);
    // Validate node existence
    if(!node)
    {
        fprintf(stderr, "[-] Node nonexistent in list_push_tail.\n");
        return  -1;
    }
    // If tail does not exist, point head and tail at node
    if(!list->tail)
    {
        list->head = node;
        list->tail = node;
        //list->tail->next = list->head;
    }
    else
    {
        // Insert node at tail->next and update tail pointer
        list->tail->next = node;
        list->tail = node;
        //list->tail->next = list->head;
    }

    // Increment size
    list->size++;

    return 0;
}

/**
 * @brief Implementation of the list_emptycheck function
 */
int list_emptycheck(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_emptycheck.\n");
        return  -1;
    }

    // Check list size
    if(list->size != 0){
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the list_pop_head function
 */
list_node_t * list_pop_head(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_pop_head.\n");
        return  NULL;
    }
    // Set current pointer to list->head
    list_node_t *popped = list->head;
    list->head = popped->next;
    // If head was only element, set tail to NULL
    if(list->head == NULL)
    {
        list->tail = NULL;
    }

    // Decrement size of list
    list->size--;

    // Reset position parameter of all nodes
    list->head->position = HEAD_POSITION;
    list_node_t *curr = list->head;
    while(curr->next)
    {
        curr = curr->next;
        curr->position++;
    }
    return popped;
}

/**
 * @brief Implementation of the list_pop_tail function
 */
list_node_t * list_pop_tail(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_push_tail.\n");
        return  NULL;
    }
    // Set current pointer to list->head
    list_node_t *curr = list->head;
    // Set previous pointer to NULL
    list_node_t *prev = NULL;
    // Iterate over list while current-> != NULL
    while(curr->next){
        prev = curr;
        curr = curr->next;
    }

    // Set prev's next to NULL, cutting off the last element
    prev->next = NULL;
    
    return curr->next;
}

/**
 * @brief Implementation of the list_peek_head function
 */
list_node_t * list_peek_head(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_peek_head.\n");
        return NULL;
    }

    return list->head;
}

/**
 * @brief Implementation of the list_peek_tail function
 */
list_node_t * list_peek_tail(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_peek_tail.\n");
        return NULL;
    }

    return list->tail;
}

/**
 * @brief Implementation of the list_remove function
 */
int list_remove(list_t * list, void ** item_to_remove)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_remove.\n");
        return NULL;
    }
    // Set current pointer to list->head
    list_node_t *curr = list->head;
    // Set previous pointer to NULL
    list_node_t *prev = NULL;

    // Find the item to remove
    while(curr)
    {
        // Check if current node holds item_to_remove
        if(list->compare_function(*item_to_remove, curr->data))
        {
            // Remove the current node
            if(curr == list->head)
            {
                // Remove node from front of list
                list->head = curr->next;
            }
            else{
                // Remove node from anywhere else in list
                prev->next = curr->next;
            }

            // Free the released node and data
            list->customfree(curr->data);
            free(curr);
            list->size--;

            // Adjust position values of upstream nodes
            int32_t pos = prev->position;
            
            while(prev->next)
            {
                prev = prev->next;
                prev->position++;
            }            
                    
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    return -1;
}

/**
 * @brief Implementation of the list_foreach_call function
 */
int list_foreach_call(list_t * list, ACT_F action_function)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_foreach_tail.\n");
        return NULL;
    }

    // Perform action_function on data of each node in list
    list_node_t *curr = list->head;
    while(curr)
    {
        action_function(curr->data);
        curr = curr->next;
    }
    return 0;
}

/**
 * @brief Implementation of the list_find_first_occurrence function
 */
list_node_t * list_find_first_occurrence(list_t * list, void ** search_data)
{
    list_node_t *curr = list->head;
    while(curr)
    {
        if(curr->data == *search_data)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
/**
 * @brief Implementation of the list_find_all_occurrences function
 */
list_t * list_find_all_occurrences(list_t * list, void ** search_data)
{
    // Instnatiate list to hold list of matches
    list_t *receiving_list;
    list_node_t *curr = list->head;
    while(curr)
    {
        if(curr->data == *search_data)
        {
            list_node_t *new_node;
            new_node->next = NULL;
            new_node->data = curr->data;
            if(!receiving_list)
            {
                receiving_list->head = new_node;
                receiving_list->tail = new_node;
            }
            else
            {
                receiving_list->tail->next = new_node;
                receiving_list->tail = new_node;
            }
        }
        curr = curr->next;
    }
    return receiving_list;
}

/**
 * @brief Implementation of the list_sort function
 */
int list_sort(list_t * list)
{
    // Selection sort on the linked list
    for(list_node_t *i = list->head; i && i->next; i = i->next)
    {
        list_node_t *min_node = i;
        for(list_node_t *j = i->next; j; j = j->next)
        {
            if(j->data < min_node->data)
            {
                min_node = j;
            }
        }
        // Perform swap of data from node i with data from min_node
        if(i != min_node)
        {
            int tmp = i->data;
            i->data = min_node->data;
            min_node->data = tmp;
        }
    }

    return 0;
}

/**
 * @brief Implementation of the list_clear function
 */
int list_clear(list_t * list)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_clear.\n");
        return NULL;
    }
    // Set curr and prev trackers
    list_node_t *curr = list->head;
    list_node_t *prev = NULL;

    while(curr)
    {
        // Set prev to curr
        prev = curr;
        // Advance curr
        curr = curr->next;

        // Free prev data and node
        list->customfree(prev->data);
        free(prev);
    }
    // Update list parameters
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return 0;
}

/**
 * @brief Implementation of the delete_list function
 */
int list_delete(list_t ** list_address)
{
    // Validate list existence
    if(!list_address || !*list_address)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_delete.\n");
        return NULL;
    }
    // Clear the list
    list_clear(*list_address);
    // Free the address
    custom_free(*list_address);
    // Set list_address to NULL to prevent dangling pointer
    *list_address = NULL;

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
}