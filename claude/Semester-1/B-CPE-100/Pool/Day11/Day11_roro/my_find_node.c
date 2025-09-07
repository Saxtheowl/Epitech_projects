#include <stddef.h>
#include "include/mylist.h"

linked_list_t *my_find_node(linked_list_t const *begin, void const *data_ref, int (*cmp)())
{
    if (cmp == NULL)
        return NULL;

    while (begin != NULL) {
        if ((*cmp)(begin->data, data_ref) == 0) {
            return (linked_list_t *)begin;
        }
        begin = begin->next;
    }

    return NULL;
}