#include <stddef.h>
#include "include/mylist.h"

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)())
{
    linked_list_t *current;
    linked_list_t *next;

    if (begin1 == NULL || cmp == NULL)
        return;

    while (begin2 != NULL) {
        next = begin2->next;
        
        if (*begin1 == NULL || (*cmp)(begin2->data, (*begin1)->data) <= 0) {
            begin2->next = *begin1;
            *begin1 = begin2;
        } else {
            current = *begin1;
            while (current->next != NULL && (*cmp)(begin2->data, current->next->data) > 0) {
                current = current->next;
            }
            begin2->next = current->next;
            current->next = begin2;
        }
        
        begin2 = next;
    }
}