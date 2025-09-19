/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 4: Display data of all connected links
*/

#include "graph.h"

void print_data_of_connected_links(link_t *link)
{
    link_list_t *current;

    if (!link)
        return;

    current = link->connections;
    while (current) {
        if (current->link)
            printf("%d\n", current->link->data);
        current = current->next;
    }
}