/*
** EPITECH PROJECT, 2024
** Day11 - my_add_in_sorted_list
** File description:
** Creates and inserts a new element into a sorted list while maintaining sorted order
*/

#include "../include/mylist.h"

void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*cmp)())
{
    linked_list_t *new_node;
    linked_list_t *current;
    linked_list_t *prev = NULL;

    if (begin == NULL || cmp == NULL)
        return;

    new_node = malloc(sizeof(linked_list_t));
    if (new_node == NULL)
        return;

    new_node->data = data;
    new_node->next = NULL;

    if (*begin == NULL || (*cmp)(data, (*begin)->data) <= 0) {
        new_node->next = *begin;
        *begin = new_node;
        return;
    }

    current = *begin;
    while (current != NULL && (*cmp)(data, current->data) > 0) {
        prev = current;
        current = current->next;
    }

    new_node->next = current;
    prev->next = new_node;
}