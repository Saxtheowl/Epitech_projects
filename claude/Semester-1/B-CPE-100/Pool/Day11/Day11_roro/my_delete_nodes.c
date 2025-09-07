#include <stdlib.h>
#include <stddef.h>
#include "include/mylist.h"

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)())
{
    linked_list_t *current;
    linked_list_t *next;
    linked_list_t *prev = NULL;
    int deleted_count = 0;

    if (begin == NULL || cmp == NULL)
        return 0;

    current = *begin;

    while (current != NULL) {
        next = current->next;
        
        if ((*cmp)(current->data, data_ref) == 0) {
            if (prev == NULL) {
                *begin = next;
            } else {
                prev->next = next;
            }
            free(current);
            deleted_count++;
        } else {
            prev = current;
        }
        
        current = next;
    }

    return deleted_count;
}