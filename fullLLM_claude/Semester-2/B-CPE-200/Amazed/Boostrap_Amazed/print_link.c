/*
** EPITECH PROJECT, 2025
** Bootstrap A-MAZE-D
** File description:
** Step 2: Display the data value of a link
*/

#include "graph.h"

void print_link(link_t *link)
{
    if (link)
        printf("%d\n", link->data);
}