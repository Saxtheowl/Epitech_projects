/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** links mode
*/

#include <stdio.h>
#include "gos.h"

int run_links(graph_t *g, const char *p1, const char *p2)
{
    int i1;
    int i2;
    int d;

    i1 = name_index(g, p1);
    i2 = name_index(g, p2);
    if (i1 < 0 || i2 < 0)
        d = -1;
    else if (i1 == i2)
        d = 0;
    else
        d = bfs_distance(g, i1, i2);
    printf("Degree of separation between %s and %s: %d\n", p1, p2, d);
    return 0;
}

