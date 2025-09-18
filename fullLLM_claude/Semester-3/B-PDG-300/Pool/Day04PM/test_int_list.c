/*
** EPITECH PROJECT, 2024
** Day04PM - Test Exercise 00
** File description:
** Test for integer list
*/

#include "int_list.h"
#include <stdio.h>

int main()
{
    int_list_t list = NULL;

    printf("Empty list test:\n");
    printf("Size: %u, Empty: %s\n", int_list_get_size(list), int_list_is_empty(list) ? "true" : "false");
    int_list_dump(list);

    printf("\nAdding elements at front: 3, 2, 1\n");
    int_list_add_elem_at_front(&list, 3);
    int_list_add_elem_at_front(&list, 2);
    int_list_add_elem_at_front(&list, 1);
    int_list_dump(list);
    printf("Size: %u\n", int_list_get_size(list));

    printf("\nAdding element at back: 4\n");
    int_list_add_elem_at_back(&list, 4);
    int_list_dump(list);

    printf("\nAdding element at position 2: 10\n");
    int_list_add_elem_at_position(&list, 10, 2);
    int_list_dump(list);

    printf("\nGetting elements:\n");
    printf("Front: %d, Back: %d, Position 2: %d\n", 
           int_list_get_elem_at_front(list),
           int_list_get_elem_at_back(list),
           int_list_get_elem_at_position(list, 2));

    printf("\nDeleting element at front\n");
    int_list_del_elem_at_front(&list);
    int_list_dump(list);

    printf("\nDeleting element at back\n");
    int_list_del_elem_at_back(&list);
    int_list_dump(list);

    printf("\nClearing list\n");
    int_list_clear(&list);
    printf("Size after clear: %u, Empty: %s\n", int_list_get_size(list), int_list_is_empty(list) ? "true" : "false");

    return 0;
}