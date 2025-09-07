#include <stddef.h>
#include "include/mylist.h"

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *prev = NULL;
    linked_list_t *current;
    linked_list_t *next;

    if (begin == NULL || *begin == NULL)
        return;

    current = *begin;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *begin = prev;
}