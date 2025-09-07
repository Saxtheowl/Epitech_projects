#include <stdlib.h>
#include <stddef.h>
#include "include/mylist.h"

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
    if (prev != NULL) {
        prev->next = new_node;
    }
}