/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** graph
*/

#include <stdlib.h>
#include <string.h>
#include "gos.h"

static void bfs_from(const graph_t *g, int src, int *out)
{
    int *q;
    int head;
    int tail;
    size_t i;

    for (i = 0; i < g->count; ++i)
        out[i] = -1;
    q = (int *)xcalloc(g->count, sizeof(int));
    head = 0;
    tail = 0;
    out[src] = 0;
    q[tail++] = src;
    while (head < tail) {
        int u = q[head++];
        for (i = 0; i < g->count; ++i) {
            if (g->adj[u][i] && out[i] == -1) {
                out[i] = out[u] + 1;
                q[tail++] = (int)i;
            }
        }
    }
    free(q);
}

void compute_all_pairs(graph_t *g)
{
    size_t i;
    g->dist = (int **)xcalloc(g->count, sizeof(int *));
    for (i = 0; i < g->count; ++i) {
        g->dist[i] = (int *)xcalloc(g->count, sizeof(int));
        bfs_from(g, (int)i, g->dist[i]);
    }
}

int bfs_distance(const graph_t *g, int a, int b)
{
    int *buf;
    int d;

    if (a < 0 || b < 0)
        return -1;
    if (!g->dist) {
        /* fallback single-source */
        buf = (int *)xcalloc(g->count, sizeof(int));
        bfs_from(g, a, buf);
        d = buf[b];
        free(buf);
        return d;
    }
    return g->dist[a][b];
}

