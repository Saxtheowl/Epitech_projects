/*
** EPITECH PROJECT, 2024
** list_operations.c
** File description:
** List operations for Push Swap
*/

#include <stdlib.h>
#include "../include/push_swap.h"

list_t *list_create(int value)
{
    list_t *node = malloc(sizeof(list_t));

    if (node == NULL)
        return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

void list_push_front(list_t **list, int value)
{
    list_t *node = list_create(value);

    if (node == NULL)
        return;
    node->next = *list;
    *list = node;
}

int list_pop_front(list_t **list)
{
    list_t *node;
    int value;

    if (list == NULL || *list == NULL)
        return 0;
    node = *list;
    value = node->value;
    *list = node->next;
    free(node);
    return value;
}

int list_size(list_t *list)
{
    int size = 0;

    while (list) {
        size++;
        list = list->next;
    }
    return size;
}

void list_free(list_t *list)
{
    list_t *next;

    while (list) {
        next = list->next;
        free(list);
        list = next;
    }
}

int list_is_sorted(list_t *list)
{
    if (list == NULL)
        return 1;
    while (list->next) {
        if (list->value > list->next->value)
            return 0;
        list = list->next;
    }
    return 1;
}