/*
** EPITECH PROJECT, 2024
** Day11 - my_rev_list
** File description:
** Reverses the order of elements in the list
*/

#include "../include/mylist.h"

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *prev = NULL;
    linked_list_t *current = *begin;
    linked_list_t *next = NULL;

    if (begin == NULL || *begin == NULL)
        return;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *begin = prev;
}