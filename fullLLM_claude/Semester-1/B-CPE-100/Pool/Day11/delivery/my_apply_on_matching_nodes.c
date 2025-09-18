/*
** EPITECH PROJECT, 2024
** Day11 - my_apply_on_matching_nodes
** File description:
** Applies function f to nodes whose data matches data_ref
*/

#include "../include/mylist.h"

int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(), void const *data_ref, int (*cmp)())
{
    linked_list_t *current = begin;
    int result = 0;

    if (f == NULL || cmp == NULL)
        return (0);

    while (current != NULL) {
        if ((*cmp)(current->data, data_ref) == 0) {
            result = (*f)(current->data);
            if (result != 0)
                return (result);
        }
        current = current->next;
    }

    return (0);
}