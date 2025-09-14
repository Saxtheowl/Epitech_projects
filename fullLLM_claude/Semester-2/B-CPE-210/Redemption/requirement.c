/*
** EPITECH PROJECT, 2024
** Redemption
** File description:
** Implementation of requirement functions for linked list operations
*/

#include "requirement.h"
#include <stddef.h>

int my_revlist_synthesis(list_t **begin)
{
    list_t *prev = NULL;
    list_t *current = *begin;
    list_t *next = NULL;
    
    if (begin == NULL)
        return -1;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    *begin = prev;
    return 0;
}

list_t *my_findnodeeqinlist_synthesis(list_t *begin, void *data_ref,
    int (*cmp)(void *, void *))
{
    list_t *current = begin;
    
    if (cmp == NULL)
        return NULL;
    
    while (current != NULL) {
        if (cmp(current->data, data_ref) == 0)
            return current;
        current = current->next;
    }
    
    return NULL;
}