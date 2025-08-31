/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Graph and BFS tools
*/

#include <stdlib.h>
#include <stdbool.h>
#include "gos.h"

static graph_t *graph_alloc(size_t n)
{
    graph_t *g = NULL;
    size_t i = 0;

    g = malloc(sizeof(graph_t));
    if (!g)
        return NULL;
    g->n = n;
    g->deg = calloc(n, sizeof(int));
    g->adj = calloc(n, sizeof(int *));
    if (!g->deg || !g->adj) {
        free(g->deg);
        free(g->adj);
        free(g);
        return NULL;
    }
    for (i = 0; i < n; ++i)
        g->adj[i] = NULL;
    return g;
}

static void count_degrees(graph_t *g, const edges_t *edges, bool undirected)
{
    size_t i = 0;
    int u = 0;
    int v = 0;

    for (i = 0; i < edges->size; ++i) {
        u = edges->items[i].from;
        v = edges->items[i].to;
        g->deg[u] += 1;
        if (undirected)
            g->deg[v] += 1;
    }
}

static bool fill_edges(graph_t *g, const edges_t *edges, bool undirected)
{
    size_t i = 0;
    int *idx = NULL;
    int u = 0;
    int v = 0;

    idx = calloc(g->n, sizeof(int));
    if (!idx)
        return false;
    for (u = 0; (size_t)u < g->n; ++u) {
        if (g->deg[u] > 0) {
            g->adj[u] = malloc(sizeof(int) * g->deg[u]);
            if (!g->adj[u]) {
                free(idx);
                return false;
            }
        }
    }
    for (i = 0; i < edges->size; ++i) {
        u = edges->items[i].from;
        v = edges->items[i].to;
        g->adj[u][idx[u]++] = v;
        if (undirected)
            g->adj[v][idx[v]++] = u;
    }
    free(idx);
    return true;
}

graph_t *graph_build_directed(size_t n, const edges_t *edges)
{
    graph_t *g = NULL;

    g = graph_alloc(n);
    if (!g)
        return NULL;
    count_degrees(g, edges, false);
    if (!fill_edges(g, edges, false)) {
        graph_destroy(g);
        return NULL;
    }
    return g;
}

graph_t *graph_build_undirected(size_t n, const edges_t *edges)
{
    graph_t *g = NULL;

    g = graph_alloc(n);
    if (!g)
        return NULL;
    count_degrees(g, edges, true);
    if (!fill_edges(g, edges, true)) {
        graph_destroy(g);
        return NULL;
    }
    return g;
}

void graph_destroy(graph_t *g)
{
    size_t i = 0;

    if (!g)
        return;
    for (i = 0; i < g->n; ++i)
        free(g->adj[i]);
    free(g->adj);
    free(g->deg);
    free(g);
}

int bfs_distance(const graph_t *g, int src, int dst)
{
    int *q = NULL;
    int *dist = NULL;
    int head = 0;
    int tail = 0;
    int u = 0;
    int i = 0;

    if (!g || src < 0 || dst < 0)
        return -1;
    if (src == dst)
        return 0;
    q = malloc(sizeof(int) * g->n);
    dist = malloc(sizeof(int) * g->n);
    if (!q || !dist) {
        free(q);
        free(dist);
        return -1;
    }
    for (i = 0; (size_t)i < g->n; ++i)
        dist[i] = -1;
    dist[src] = 0;
    q[tail++] = src;
    while (head < tail) {
        u = q[head++];
        for (i = 0; i < g->deg[u]; ++i) {
            int v = g->adj[u][i];
            if (dist[v] != -1)
                continue;
            dist[v] = dist[u] + 1;
            if (v == dst) {
                int d = dist[v];
                free(q);
                free(dist);
                return d;
            }
            q[tail++] = v;
        }
    }
    free(q);
    free(dist);
    return -1;
}

static int *bfs_all_dist(const graph_t *g, int src)
{
    int *q = NULL;
    int *dist = NULL;
    int head = 0;
    int tail = 0;
    int u = 0;
    int i = 0;

    q = malloc(sizeof(int) * g->n);
    dist = malloc(sizeof(int) * g->n);
    if (!q || !dist) {
        free(q);
        free(dist);
        return NULL;
    }
    for (i = 0; (size_t)i < g->n; ++i)
        dist[i] = -1;
    dist[src] = 0;
    q[tail++] = src;
    while (head < tail) {
        u = q[head++];
        for (i = 0; i < g->deg[u]; ++i) {
            int v = g->adj[u][i];
            if (dist[v] != -1)
                continue;
            dist[v] = dist[u] + 1;
            q[tail++] = v;
        }
    }
    free(q);
    return dist;
}

int *single_source_distances(const graph_t *g, int src)
{
    return bfs_all_dist(g, src);
}

int *all_pairs_distances_n(const graph_t *g, int limit)
{
    int *mat = NULL;
    int *dist = NULL;
    size_t i = 0;
    size_t j = 0;

    mat = malloc(sizeof(int) * g->n * g->n);
    if (!mat)
        return NULL;
    for (i = 0; i < g->n; ++i) {
        dist = bfs_all_dist(g, (int)i);
        if (!dist) {
            free(mat);
            return NULL;
        }
        for (j = 0; j < g->n; ++j) {
            int d = dist[j];
            if ((int)i == (int)j)
                mat[i * g->n + j] = 0;
            else if (d != -1 && d <= limit)
                mat[i * g->n + j] = d;
            else
                mat[i * g->n + j] = 0;
        }
        free(dist);
    }
    return mat;
}

static int prefer_candidate(int ia, int ib, int queen,
    const graph_t *cr, const name_list_t *names, const int *distq)
{
    int i = 0;
    bool a_plots_q = false;
    bool b_plots_q = false;
    int da = 0;
    int db = 0;

    for (i = 0; i < cr->deg[ia]; ++i)
        if (cr->adj[ia][i] == queen)
            a_plots_q = true;
    for (i = 0; i < cr->deg[ib]; ++i)
        if (cr->adj[ib][i] == queen)
            b_plots_q = true;
    if (a_plots_q != b_plots_q)
        return a_plots_q ? 1 : -1;
    da = distq[ia] == -1 ? 1000000 : distq[ia];
    db = distq[ib] == -1 ? 1000000 : distq[ib];
    if (da != db)
        return (da < db) ? -1 : 1;
    return gos_strcmp(names->items[ia], names->items[ib]);
}

bool find_chain(const graph_t *cr, const int *dist_to_queen,
    const bool *is_direct_enemy, int queen_idx, int n, int target,
    int *out_path, int *out_len, const name_list_t *names)
{
    int *rev_deg = NULL;
    int **rev_adj = NULL;
    int *q = NULL;
    int *par = NULL;
    int head = 0;
    int tail = 0;
    int u = 0;
    int i = 0;
    int src = -1;

    (void)is_direct_enemy;
    rev_deg = calloc(cr->n, sizeof(int));
    rev_adj = calloc(cr->n, sizeof(int *));
    par = malloc(sizeof(int) * cr->n);
    q = malloc(sizeof(int) * cr->n);
    if (!rev_deg || !rev_adj || !par || !q)
        goto fail;
    for (u = 0; (size_t)u < cr->n; ++u) {
        for (i = 0; i < cr->deg[u]; ++i)
            rev_deg[cr->adj[u][i]] += 1;
        par[u] = -1;
    }
    for (u = 0; (size_t)u < cr->n; ++u) {
        if (rev_deg[u] > 0) {
            rev_adj[u] = malloc(sizeof(int) * rev_deg[u]);
            if (!rev_adj[u])
                goto fail;
            rev_deg[u] = 0;
        }
    }
    for (u = 0; (size_t)u < cr->n; ++u) {
        for (i = 0; i < cr->deg[u]; ++i) {
            int v = cr->adj[u][i];
            rev_adj[v][rev_deg[v]++] = u;
        }
    }
    head = 0;
    tail = 0;
    q[tail++] = target;
    par[target] = -2;
    while (head < tail) {
        int cur = q[head++];
        int deg = 0;
        int *cand = NULL;

        deg = rev_deg[cur];
        if (deg > 0) {
            cand = malloc(sizeof(int) * deg);
            if (!cand)
                goto fail;
            for (i = 0; i < deg; ++i)
                cand[i] = rev_adj[cur][i];
            /* simple selection sort with project-specific priority */
            for (i = 0; i < deg; ++i) {
                int j = 0;
                int best = i;
                for (j = i + 1; j < deg; ++j) {
                    if (prefer_candidate(cand[j], cand[best], queen_idx,
                        cr, names, dist_to_queen) < 0)
                        best = j;
                }
                if (best != i) {
                    int t = cand[i];
                    cand[i] = cand[best];
                    cand[best] = t;
                }
            }
            for (i = 0; i < deg; ++i) {
                int v = cand[i];
                if (par[v] != -1)
                    continue;
                par[v] = cur;
                if (dist_to_queen[v] != -1 && dist_to_queen[v] <= n) {
                    src = v;
                    free(cand);
                    goto build;
                }
                q[tail++] = v;
            }
            free(cand);
        }
    }
    for (u = 0; (size_t)u < cr->n; ++u)
        free(rev_adj[u]);
    free(rev_adj);
    free(rev_deg);
    free(par);
    free(q);
    return false;

build:
    {
        int len = 0;
        int cur = src;
        while (cur != -2) {
            out_path[len++] = cur;
            cur = par[cur];
        }
        *out_len = len;
    }
    for (u = 0; (size_t)u < cr->n; ++u)
        free(rev_adj[u]);
    free(rev_adj);
    free(rev_deg);
    free(par);
    free(q);
    return true;

fail:
    if (rev_adj) {
        for (u = 0; rev_adj && (size_t)u < cr->n; ++u)
            free(rev_adj[u]);
    }
    free(rev_adj);
    free(rev_deg);
    free(par);
    free(q);
    return false;
}
