#include <stdlib.h>
#include "include/mylist.h"

linked_list_t *my_params_to_list(int ac, char * const *av)
{
    linked_list_t *list = NULL;
    linked_list_t *new_node;
    int i;

    if (ac <= 0 || av == NULL)
        return NULL;

    for (i = 0; i < ac; i++) {
        new_node = malloc(sizeof(linked_list_t));
        if (new_node == NULL)
            return list;
        
        new_node->data = (void *)av[i];
        new_node->next = list;
        list = new_node;
    }

    return list;
}