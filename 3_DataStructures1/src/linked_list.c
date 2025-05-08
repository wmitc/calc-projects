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

#define HEAD_POSITION 0
#define SIZE_OF_1 1

/**
 * @brief Create a node object
 * 
 * @param data data for node to hold
 * @param position position relevant to head (0)
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
    if(!node)
    {
        fprintf(stderr, "[-] Null value passed to default_compare function.\n");
        return 1;       
    }
    int find_value = *(int *) value_to_find;
    int node_value = *(int *) node;
    //printf("compare result: %d\n", node_value - find_value);
    return (void *) node_value - find_value;
}

/**
 * @brief Compare value_to_find with data stored in a node
 * 
 * @param value_to_find 
 * @param node 
 * @return node on success, NULL on failure
 */
void * node_compare(int value_to_find, void * node)
{
    if(!node)
    {
        fprintf(stderr, "[-] Null value passed to node_compare function.\n");
        return 1;         
    }
    //printf("value to find %d\n", value_to_find);
    //printf("value of node %d\n", *(int *)((list_node_t *)node)->data);
    void *retval = NULL;

    if(*(int *)((list_node_t *)node)->data == value_to_find)
    {
        retval = node;
    }

    return retval;
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
        return  1;
    }
    // Create new node
    list_node_t *node = create_node(data, HEAD_POSITION);
    // Validate node existence
    if(!node)
    {
        fprintf(stderr, "[-] Node nonexistent in list_push_tail.\n");
        return  1;
    }

    // Set node->next for push_head
    node->next = list->head; // list->head will be NULL if list->size is 0
    list->head = node;

    // If list is empty, point tail to new node
    if(list->size == 0)
    {
        list->tail = node;
    }
    else
    {
        // Iterate over list, from head->next to end, incrementing position
        list_node_t *curr = list->head->next;
        while(curr)
        {
            curr->position++;
            curr = curr->next;       
        }
    }
    // Make circular?
    //list->tail->next = list->head;

    // Increment size
    list->size++;

    return 0;
}

/**
 * @brief Implementation of the list_push_tail function
 */
int list_push_tail(list_t * list, void * data)
{
    //printf("size: %d\n", list->size);
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_push_tail.\n");
        return  1;
    }
    // Create new node
    list_node_t *node = create_node(data, list->size);
    // Validate node existence
    if(!node)
    {
        fprintf(stderr, "[-] Node nonexistent in list_push_tail.\n");
        return  1;
    }
    // If list is empty, point head and tail at node
    if(list->size == 0)
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
        return 1;
    }

    // Check list size
    if(list->size == 0){
        return 1;
    }

    return 0;
}

/**
 * @brief Implementation of the list_pop_head function
 */
list_node_t * list_pop_head(list_t * list)
{
    //printf("size: %d\n", list->size);
    // Validate list existence
    if(!list || list_emptycheck(list))
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_pop_head.\n");
        return  NULL;
    }

    // Set current pointer to list->head
    list_node_t *popped = list->head;
    list->head = popped->next;

    // Decrement size of list
    list->size--;
    
    // If head was only element, set tail to NULL
    if(list->size == 0)
    {
        list->tail = NULL;
        return popped;
    }
    else{
        // Reset position parameter of all nodes
        list->head->position = HEAD_POSITION;
        list_node_t *curr = list->head;
        while(curr->next)
        {
            curr = curr->next;
            curr->position--;
        }
        return popped;
    }
}

/**
 * @brief Implementation of the list_pop_tail function
 */
list_node_t * list_pop_tail(list_t * list)
{
    // Validate list existence
    if(!list || list_emptycheck(list))
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_push_tail.\n");
        return  NULL;
    }


    // Check if list size is 1
    if(list->size == 1)
    {
        list_node_t *curr = list->head;
        list->head = NULL;
        list->tail = NULL;

        // Decrement size of list
        list->size--;

        return curr;    
    }
    else
    {
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
        list->tail = prev;

        // Decrement size of list
        list->size--;

        return curr;
    }  
}

/**
 * @brief Implementation of the list_peek_head function
 */
list_node_t * list_peek_head(list_t * list)
{
    // Validate list existence
    if(!list || list_emptycheck(list))
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
    if(!list || list_emptycheck(list))
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

    //printf("item to remove: %d\n", *(int *) item_to_remove);
    // Validate list existence
    if(!list || list_emptycheck(list))
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_remove.\n");
        return 1;
    }

    // Set current pointer to list->head
    list_node_t *curr = list->head;
    // Set previous pointer to NULL
    list_node_t *prev = NULL;    

    while(curr)
    {
        // Check whether item_to_remove is at head node
        //if(list->compare_function(item_to_remove, curr->data) == 0)
        if(node_compare(*item_to_remove, curr))
        {
            // Check if head holds item_to_remove
            if(curr == list->head)
            {
                list->head = curr->next;
            }
            else
            {
                // If curr is not head, prev will not be NULL
                prev->next = curr->next;
            }
            list_node_t *update_pos = curr->next;
            free(curr);

            // Update list size
            list->size--;

            // Update upstream positions
            while(update_pos)
            {
                update_pos->position--;
                update_pos = update_pos->next;   
            }


            return 0;
        }

        prev = curr;
        curr = curr->next;

    }

    return 1;
}

/**
 * @brief Implementation of the list_foreach_call function
 */
int list_foreach_call(list_t * list, ACT_F action_function)
{
    // Validate list existence
    if(!list)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_foreach_call.\n");
        return 1;
    }
    // Validate action function
    if(!action_function)
    {
        fprintf(stderr, "[-] Linked list missing action_function in list_foreach_call.\n");
        return 1;
    }
    // Perform action_function on data of each node in list
    list_node_t *curr = list->head;
    while(curr)
    {

        *(int *)curr->data %=2;
        //action_function(curr->data);

        curr = curr->next;
    }
    return 0;
}

/**
 * @brief Implementation of the list_find_first_occurrence function
 */
list_node_t * list_find_first_occurrence(list_t * list, void ** search_data)
{
    // Validate list existence
    if(!list || list->size == 0)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_find_first_occurrence.\n");
        return NULL;
    }
    // Find first occurrence
    list_node_t *curr = list->head;
    while(curr)
    {
        if(node_compare(*search_data, curr)) 
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
    // Validate list existence
    if(!list || list->size == 0)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_find_all_occurrences.\n");
        return NULL;
    }
    // Instnatiate list to hold list of matches
    list_t *receiving_list = malloc(sizeof(list_t));
    // Initialize list parameters
    receiving_list->size = 0;
    receiving_list->head = NULL;
    receiving_list->tail = NULL;
    receiving_list->customfree = custom_free;
    receiving_list->compare_function = node_compare;
    list_node_t *curr = list->head;
    uint32_t pos = 0;
    while(curr)
    {
        if(node_compare(*search_data, curr))
        {
            // Allocate new node
            list_node_t *new_node = malloc(sizeof(list_node_t));
            new_node->next = NULL;
            new_node->data = curr->data;
            new_node->position = pos;
            if(!receiving_list->head)
            {
                receiving_list->head = new_node;
                receiving_list->tail = new_node;
            }
            else
            {
                receiving_list->tail->next = new_node;
                receiving_list->tail = new_node;
            }
            // Increment list size
            receiving_list->size++;
            // Increment position value
            pos++;
        }
        // Move to next node
        curr = curr->next;
    }
    return receiving_list;
}

/**
 * @brief Implementation of the list_sort function
 */
int list_sort(list_t * list)
{
    // Validate list existence
    if(!list || !list->head)
    {
        fprintf(stderr, "[-] Linked list nonexistent in list_sort.\n");
        return 1;
    }


    // Selection sort on the linked list
    for(list_node_t *i = list->head; i != list->tail; i = i->next)
    {
        list_node_t *min_node = i;
        for(list_node_t *j = i->next; j; j = j->next)
        {
            //printf("j->data: %d\n", *(int *) j->data);
            //printf("min_node->data: %d\n", *(int *) min_node->data);
            if((int)list->compare_function(min_node->data, j->data) < 0)
            {
                min_node = j;
            }
        }
        //printf("min_node->data ***************: %d\n", *(int *) min_node->data);
        // Perform swap of data from node i with data from min_node
        if(i != min_node)
        {
            void *tmp = i->data;
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
        return 1;
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
        //list->customfree(prev->data);
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
        return 1;
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
    if(mem_addr)
    {
        free(mem_addr);
    }
}

int main()
{
    printf("Initial array: [1, 2, 3, 4, 5]\n");
    int data[5] = {1,2,3,4,5};
    
    list_t *list = list_new(custom_free, default_compare);
    
    for(int i = 0; i < 5; i++)
    {
        //list_node_t *new_node = create_node(&data[i], i);
        list_push_head(list, &data[i]);
        //free(new_node);
    }
    printf("size: %d\n", list->size);
    // Now print the conents of the queue
    list_node_t *curr = list->head;

    while(curr)
    {
        printf("Node %d has data %d\n",curr->position,*(int *) curr->data);
        curr = curr->next;
    }


    printf("sorted!\n");

    list_sort(list);

    curr = list->head;
    while(curr)
    {
        printf("Node %d has data %d\n",curr->position,*(int *) curr->data);
        curr = curr->next;
    }

}