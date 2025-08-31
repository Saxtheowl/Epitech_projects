/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** plots mode
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "gos.h"

/* no qsort_r helper needed */

static int *sorted_order(const graph_t *g)
{
    int *ord;
    size_t i;

    ord = (int *)xcalloc(g->count, sizeof(int));
    for (i = 0; i < g->count; ++i)
        ord[i] = (int)i;
    /* Portable sort by name */
    for (i = 0; i + 1 < g->count; ++i) {
        size_t j;
        for (j = i + 1; j < g->count; ++j) {
            if (strcmp(g->names[ord[i]], g->names[ord[j]]) > 0) {
                int t = ord[i];
                ord[i] = ord[j];
                ord[j] = t;
            }
        }
    }
    return ord;
}

static void print_names(const graph_t *g, const int *ord)
{
    size_t i;

    printf("Names:\n");
    for (i = 0; i < g->count; ++i)
        printf("%s\n", g->names[ord[i]]);
}

static void print_relationships(const graph_t *g, const int *ord, int n)
{
    size_t i;
    size_t j;
    int d;

    printf("Relationships:\n");
    for (i = 0; i < g->count; ++i) {
        for (j = 0; j < g->count; ++j) {
            d = g->dist[ord[i]][ord[j]];
            if (d < 0 || d > n)
                d = 0;
            printf("%d%s", d, (j + 1 < g->count) ? " " : "\n");
        }
    }
}

static bool is_close_friend(const graph_t *g, int crown, int v, int n)
{
    int d;

    d = g->dist[crown][v];
    return (d >= 0 && d <= n);
}

static int bfs_cr_path_find(const graph_t *g, int enemy, int crown, int n,
    int *parent)
{
    int *q;
    int head;
    int tail;
    size_t i;
    int *ord;

    for (i = 0; i < g->count; ++i)
        parent[i] = -2; /* -2 = unvisited, -1 = root */
    q = (int *)xcalloc(g->count, sizeof(int));
    ord = sorted_order(g);
    head = 0;
    tail = 0;
    parent[enemy] = -1;
    q[tail++] = enemy;
    while (head < tail) {
        int u = q[head++];
        for (i = 0; i < g->count; ++i) {
            int v = ord[i];
            if (!g->cr_in[u][v])
                continue;
            if (parent[v] != -2)
                continue;
            parent[v] = u;
            /* stop early if we reached any close friend */
            if (is_close_friend(g, crown, v, n)) {
                free(ord);
                free(q);
                return v;
            }
            q[tail++] = v;
        }
    }
    free(ord);
    free(q);
    return -1;
}

static void print_chain(const graph_t *g, int src, int dst, const int *parent)
{
    int u;
    u = src;
    while (u != -1) {
        printf("%s", g->names[u]);
        if (u == dst)
            break;
        printf(" -> ");
        u = parent[u];
    }
    printf("\n");
}

int run_plots(graph_t *g, const char *cr, int n)
{
    int *ord;
    int crown;
    size_t i;
    int any_miss;

    if (load_cr(cr, g) != 0)
        return 84;
    compute_all_pairs(g);
    ord = sorted_order(g);
    print_names(g, ord);
    print_relationships(g, ord, n);
    free(ord);

    crown = name_index(g, crown_name);
    printf("Conspiracies:\n");
    any_miss = 0;
    for (i = 0; i < g->count; ++i) {
        int enemy = (int)i;
    int *parent;
    int start;

        if (!g->cr_out[enemy][crown])
            continue;
        parent = (int *)xcalloc(g->count, sizeof(int));
        start = bfs_cr_path_find(g, enemy, crown, n, parent);
        if (start >= 0) {
            print_chain(g, start, enemy, parent);
        } else {
            printf("No conspiracy possible against %s\n", g->names[enemy]);
            any_miss = 1;
        }
        free(parent);
    }
    printf("Result:\n");
    if (any_miss)
        printf("There is only one way out: treason!\n");
    else
        printf("The stone is safe!\n");
    return 0;
}
