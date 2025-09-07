#include <stddef.h>
#include "include/mylist.h"

void my_sort_list(linked_list_t **begin, int (*cmp)())
{
    linked_list_t *current;
    linked_list_t *next;
    void *temp_data;
    int swapped;

    if (begin == NULL || *begin == NULL || cmp == NULL)
        return;

    do {
        swapped = 0;
        current = *begin;

        while (current != NULL && current->next != NULL) {
            next = current->next;
            
            if ((*cmp)(current->data, next->data) > 0) {
                temp_data = current->data;
                current->data = next->data;
                next->data = temp_data;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}