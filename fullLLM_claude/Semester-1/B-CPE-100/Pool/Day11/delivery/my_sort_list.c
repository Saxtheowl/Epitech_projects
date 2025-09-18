/*
** EPITECH PROJECT, 2024
** Day11 - my_sort_list
** File description:
** Sorts the list in ascending order using the comparison function
*/

#include "../include/mylist.h"

void my_sort_list(linked_list_t **begin, int (*cmp)())
{
    linked_list_t *current;
    linked_list_t *next_node;
    void *temp_data;
    int swapped;

    if (begin == NULL || *begin == NULL || cmp == NULL)
        return;

    do {
        swapped = 0;
        current = *begin;

        while (current->next != NULL) {
            next_node = current->next;
            if ((*cmp)(current->data, next_node->data) > 0) {
                temp_data = current->data;
                current->data = next_node->data;
                next_node->data = temp_data;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}