/*
** EPITECH PROJECT, 2024
** Day11 - my_merge
** File description:
** Merges two sorted lists into begin1, maintaining ascending order
*/

#include "../include/mylist.h"

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)())
{
    linked_list_t *current1;
    linked_list_t *current2;
    linked_list_t *prev = NULL;
    linked_list_t *temp;

    if (begin1 == NULL || cmp == NULL)
        return;

    if (*begin1 == NULL) {
        *begin1 = begin2;
        return;
    }

    if (begin2 == NULL)
        return;

    current1 = *begin1;
    current2 = begin2;

    if ((*cmp)(current2->data, current1->data) < 0) {
        *begin1 = current2;
        current2 = current2->next;
        (*begin1)->next = current1;
        prev = *begin1;
    }

    while (current1 != NULL && current2 != NULL) {
        if ((*cmp)(current2->data, current1->data) < 0) {
            temp = current2->next;
            if (prev != NULL)
                prev->next = current2;
            current2->next = current1;
            prev = current2;
            current2 = temp;
        } else {
            prev = current1;
            current1 = current1->next;
        }
    }

    if (current2 != NULL && prev != NULL) {
        prev->next = current2;
    }
}