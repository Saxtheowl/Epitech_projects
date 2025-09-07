#include <stddef.h>
#include "include/mylist.h"

int my_list_size(linked_list_t const *begin)
{
    int count = 0;
    
    while (begin != NULL) {
        count++;
        begin = begin->next;
    }
    
    return count;
}