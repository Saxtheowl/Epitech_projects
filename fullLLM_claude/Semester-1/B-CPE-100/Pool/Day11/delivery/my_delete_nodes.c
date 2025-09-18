/*
** EPITECH PROJECT, 2024
** Day11 - my_delete_nodes
** File description:
** Removes all nodes containing data equal to data_ref
*/

#include "../include/mylist.h"

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)())
{
    linked_list_t *current;
    linked_list_t *prev = NULL;
    linked_list_t *to_delete;
    int deleted_count = 0;

    if (begin == NULL || *begin == NULL || cmp == NULL)
        return (0);

    current = *begin;

    while (current != NULL) {
        if ((*cmp)(current->data, data_ref) == 0) {
            to_delete = current;
            if (prev == NULL) {
                *begin = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_delete);
            deleted_count++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return (deleted_count);
}