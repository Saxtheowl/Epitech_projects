/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 3: Connect one link to another (unidirectional)
*/

#include "graph.h"

void connect_links(link_t *link1, link_t *link2)
{
    link_list_t *new_connection;

    if (!link1 || !link2)
        return;

    new_connection = malloc(sizeof(link_list_t));
    if (!new_connection)
        return;

    new_connection->link = link2;
    new_connection->next = link1->connections;
    link1->connections = new_connection;
}