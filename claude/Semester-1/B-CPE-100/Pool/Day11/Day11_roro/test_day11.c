#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/mylist.h"
#include "include/my.h"

int print_str(void *data)
{
    printf("Data: %s\n", (char *)data);
    return 1;
}

int test_cmp(void *a, void *b)
{
    return my_strcmp((char *)a, (char *)b);
}

void print_list(linked_list_t *list)
{
    while (list != NULL) {
        printf("-> %s ", (char *)list->data);
        list = list->next;
    }
    printf("(end)\n");
}

int main(int ac, char **av)
{
    linked_list_t *list;
    linked_list_t *found_node;
    int size;

    printf("=== Day11 Linked Lists Test ===\n\n");

    printf("1. Testing my_params_to_list:\n");
    list = my_params_to_list(ac, av);
    print_list(list);

    printf("\n2. Testing my_list_size:\n");
    size = my_list_size(list);
    printf("List size: %d\n", size);

    printf("\n3. Testing my_rev_list:\n");
    my_rev_list(&list);
    print_list(list);

    printf("\n4. Testing my_apply_on_nodes:\n");
    my_apply_on_nodes(list, print_str);

    printf("\n5. Testing my_find_node:\n");
    if (ac > 1) {
        found_node = my_find_node(list, av[1], test_cmp);
        if (found_node) {
            printf("Found node with data: %s\n", (char *)found_node->data);
        } else {
            printf("Node not found\n");
        }
    }

    printf("\n6. Testing my_sort_list:\n");
    my_sort_list(&list, test_cmp);
    print_list(list);

    return 0;
}