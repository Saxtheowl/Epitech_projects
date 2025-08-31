/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Links mode
*/

#include <stdio.h>
#include <stdlib.h>
#include "gos.h"

static int compare_alpha(const void *a, const void *b)
{
    const char *const *sa = a;
    const char *const *sb = b;
    return gos_strcmp(*sa, *sb);
}

static name_list_t sorted_names_copy(const name_list_t *names)
{
    name_list_t out;
    size_t i = 0;

    out.items = malloc(sizeof(char *) * names->size);
    out.size = names->size;
    out.cap = names->size;
    if (!out.items) {
        out.size = 0;
        out.cap = 0;
        return out;
    }
    for (i = 0; i < names->size; ++i)
        out.items[i] = names->items[i];
    qsort(out.items, out.size, sizeof(char *), compare_alpha);
    return out;
}

int run_links_mode(const char *fr, const char *p1, const char *p2)
{
    name_list_t names;
    edges_t fedges;
    graph_t *fg = NULL;
    int a = 0;
    int b = 0;
    int d = 0;

    if (!parse_friendships(fr, &names, &fedges))
        return GOS_EXIT_ERROR;
    fg = graph_build_undirected(names.size, &fedges);
    if (!fg)
        return GOS_EXIT_ERROR;
    a = get_index(&names, p1);
    b = get_index(&names, p2);
    if (a < 0 || b < 0) {
        d = -1;
    } else {
        d = bfs_distance(fg, a, b);
    }
    fprintf(stdout, "Degree of separation between %s and %s: %d\n",
        p1, p2, d);
    graph_destroy(fg);
    free(fedges.items);
    free(names.items);
    return 0;
}
