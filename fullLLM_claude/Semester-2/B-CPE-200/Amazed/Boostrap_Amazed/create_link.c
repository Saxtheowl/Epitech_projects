/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 1: Create a new link_t element
*/

#include "graph.h"

link_t *create_link(int data)
{
    link_t *new_link = malloc(sizeof(link_t));

    if (!new_link)
        return NULL;

    new_link->data = data;
    new_link->connections = NULL;

    return new_link;
}