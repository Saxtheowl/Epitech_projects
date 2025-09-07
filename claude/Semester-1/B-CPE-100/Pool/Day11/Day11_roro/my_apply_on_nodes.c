#include <stddef.h>
#include "include/mylist.h"

int my_apply_on_nodes(linked_list_t *begin, int (*f)(void *))
{
    int result = 0;

    if (f == NULL)
        return 0;

    while (begin != NULL) {
        result += (*f)(begin->data);
        begin = begin->next;
    }

    return result;
}