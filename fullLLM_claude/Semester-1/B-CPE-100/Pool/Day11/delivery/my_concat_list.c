/*
** EPITECH PROJECT, 2024
** Day11 - my_concat_list
** File description:
** Appends begin2 list to the end of begin1 list
*/

#include "../include/mylist.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2)
{
    linked_list_t *current;

    if (begin1 == NULL || begin2 == NULL)
        return;

    if (*begin1 == NULL) {
        *begin1 = begin2;
        return;
    }

    current = *begin1;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = begin2;
}