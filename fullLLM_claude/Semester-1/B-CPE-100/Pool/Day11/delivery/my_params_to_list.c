/*
** EPITECH PROJECT, 2024
** Day11 - my_params_to_list
** File description:
** Creates linked list from command line arguments in reverse order
*/

#include "../include/mylist.h"

linked_list_t *my_params_to_list(int ac, char * const *av)
{
    linked_list_t *head;
    linked_list_t *new_node;
    int i;

    if (ac <= 0 || av == NULL)
        return (NULL);

    head = NULL;
    
    for (i = ac - 1; i >= 0; i--) {
        new_node = malloc(sizeof(linked_list_t));
        if (new_node == NULL)
            return (NULL);
        
        new_node->data = (void *)av[i];
        new_node->next = head;
        head = new_node;
    }
    
    return (head);
}