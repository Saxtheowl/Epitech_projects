/*
** EPITECH PROJECT, 2024
** Day04PM - Exercise 00
** File description:
** Integer list implementation
*/

#include "int_list.h"
#include <stdio.h>
#include <stdlib.h>

/* Information Functions */

unsigned int int_list_get_size(int_list_t list)
{
    unsigned int size = 0;
    int_node_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

bool int_list_is_empty(int_list_t list)
{
    return list == NULL;
}

void int_list_dump(int_list_t list)
{
    int_node_t *current = list;

    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL)
            printf(" -> ");
        current = current->next;
    }
    printf("\n");
}

/* Modification Functions */

bool int_list_add_elem_at_front(int_list_t *front_ptr, int elem)
{
    int_node_t *new_node;

    if (front_ptr == NULL)
        return false;
    
    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;
    
    new_node->value = elem;
    new_node->next = *front_ptr;
    *front_ptr = new_node;
    return true;
}

bool int_list_add_elem_at_back(int_list_t *front_ptr, int elem)
{
    int_node_t *new_node;
    int_node_t *current;

    if (front_ptr == NULL)
        return false;
    
    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;
    
    new_node->value = elem;
    new_node->next = NULL;
    
    if (*front_ptr == NULL) {
        *front_ptr = new_node;
        return true;
    }
    
    current = *front_ptr;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
    return true;
}

bool int_list_add_elem_at_position(int_list_t *front_ptr, int elem, unsigned int position)
{
    int_node_t *new_node;
    int_node_t *current;
    unsigned int i;

    if (front_ptr == NULL)
        return false;
    
    if (position == 0)
        return int_list_add_elem_at_front(front_ptr, elem);
    
    current = *front_ptr;
    for (i = 0; i < position - 1 && current != NULL; i++)
        current = current->next;
    
    if (current == NULL)
        return false;
    
    new_node = malloc(sizeof(int_node_t));
    if (new_node == NULL)
        return false;
    
    new_node->value = elem;
    new_node->next = current->next;
    current->next = new_node;
    return true;
}

bool int_list_del_elem_at_front(int_list_t *front_ptr)
{
    int_node_t *to_delete;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;
    
    to_delete = *front_ptr;
    *front_ptr = (*front_ptr)->next;
    free(to_delete);
    return true;
}

bool int_list_del_elem_at_back(int_list_t *front_ptr)
{
    int_node_t *current;
    int_node_t *prev;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;
    
    if ((*front_ptr)->next == NULL) {
        free(*front_ptr);
        *front_ptr = NULL;
        return true;
    }
    
    current = *front_ptr;
    prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    prev->next = NULL;
    free(current);
    return true;
}

bool int_list_del_elem_at_position(int_list_t *front_ptr, unsigned int position)
{
    int_node_t *current;
    int_node_t *to_delete;
    unsigned int i;

    if (front_ptr == NULL || *front_ptr == NULL)
        return false;
    
    if (position == 0)
        return int_list_del_elem_at_front(front_ptr);
    
    current = *front_ptr;
    for (i = 0; i < position - 1 && current != NULL; i++)
        current = current->next;
    
    if (current == NULL || current->next == NULL)
        return false;
    
    to_delete = current->next;
    current->next = to_delete->next;
    free(to_delete);
    return true;
}

void int_list_clear(int_list_t *front_ptr)
{
    int_node_t *current;
    int_node_t *next;

    if (front_ptr == NULL)
        return;
    
    current = *front_ptr;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *front_ptr = NULL;
}

/* Value Access Functions */

int int_list_get_elem_at_front(int_list_t list)
{
    if (list == NULL)
        return 0; // Could be handled with error, but spec doesn't specify
    return list->value;
}

int int_list_get_elem_at_back(int_list_t list)
{
    int_node_t *current = list;

    if (list == NULL)
        return 0;
    
    while (current->next != NULL)
        current = current->next;
    return current->value;
}

int int_list_get_elem_at_position(int_list_t list, unsigned int position)
{
    int_node_t *current = list;
    unsigned int i;

    for (i = 0; i < position && current != NULL; i++)
        current = current->next;
    
    if (current == NULL)
        return 0;
    return current->value;
}