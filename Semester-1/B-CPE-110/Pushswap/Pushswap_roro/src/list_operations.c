/*
** EPITECH PROJECT, 2024
** Pushswap
** File description:
** List operations implementation
*/

#include "../include/push_swap.h"

list_t *create_list(void)
{
    list_t *list = malloc(sizeof(list_t));
    
    if (!list)
        return NULL;
    
    list->head = NULL;
    list->size = 0;
    
    return list;
}

void free_list(list_t *list)
{
    node_t *current;
    node_t *next;
    
    if (!list)
        return;
    
    current = list->head;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

void push_front(list_t *list, int value)
{
    node_t *new_node;
    
    if (!list)
        return;
    
    new_node = malloc(sizeof(node_t));
    if (!new_node)
        return;
    
    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

int pop_front(list_t *list)
{
    node_t *to_remove;
    int value;
    
    if (!list || !list->head)
        return 0;
    
    to_remove = list->head;
    value = to_remove->value;
    list->head = list->head->next;
    free(to_remove);
    list->size--;
    
    return value;
}

int is_empty(list_t *list)
{
    if (!list)
        return 1;
    return list->head == NULL;
}

int is_sorted(list_t *list)
{
    node_t *current;
    
    if (!list || !list->head)
        return 1;
    
    current = list->head;
    while (current->next) {
        if (current->value > current->next->value)
            return 0;
        current = current->next;
    }
    
    return 1;
}