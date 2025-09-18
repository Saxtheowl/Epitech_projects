/*
** EPITECH PROJECT, 2024
** Day11 - my_apply_on_nodes
** File description:
** Applies a function to the data of each node in the list
*/

#include "../include/mylist.h"

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *))
{
    linked_list_t *current = begin;
    int result = 0;

    if (f == NULL)
        return (0);

    while (current != NULL) {
        result = (*f)(current->data);
        if (result != 0)
            return (result);
        current = current->next;
    }

    return (0);
}