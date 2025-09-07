#include <stddef.h>
#include "include/mylist.h"

int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(), void const *data_ref, int (*cmp)())
{
    int result = 0;

    if (f == NULL || cmp == NULL)
        return 0;

    while (begin != NULL) {
        if ((*cmp)(begin->data, data_ref) == 0) {
            result += (*f)(begin->data);
        }
        begin = begin->next;
    }

    return result;
}