/*
** EPITECH PROJECT, 2024
** Day11 - my_list_size
** File description:
** Returns the number of elements in the list
*/

#include "../include/mylist.h"

int my_list_size(linked_list_t const *begin)
{
    int count = 0;
    linked_list_t const *current = begin;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return (count);
}