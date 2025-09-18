/*
** EPITECH PROJECT, 2024
** Day11 - my_find_node
** File description:
** Returns address of first node containing data equal to data_ref
*/

#include "../include/mylist.h"

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref, int (*cmp)())
{
    linked_list_t const *current = begin;

    if (cmp == NULL)
        return (NULL);

    while (current != NULL) {
        if ((*cmp)(current->data, data_ref) == 0) {
            return ((linked_list_t *)current);
        }
        current = current->next;
    }

    return (NULL);
}