/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Plots mode
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gos.h"

static int compare_alpha_ptr(const void *a, const void *b)
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
    qsort(out.items, out.size, sizeof(char *), compare_alpha_ptr);
    return out;
}

static int index_in_sorted(const name_list_t *sorted, const char *name)
{
    size_t i = 0;

    for (i = 0; i < sorted->size; ++i) {
        if (gos_strcmp(sorted->items[i], name) == 0)
            return (int)i;
    }
    return -1;
}

static int *build_matrix(const graph_t *fg, const name_list_t *names,
    const name_list_t *sorted, int limit)
{
    size_t n = names->size;
    int *mat = NULL;
    int *dist = NULL;
    size_t i = 0;
    size_t j = 0;
    int si = 0;
    int sj = 0;

    mat = malloc(sizeof(int) * n * n);
    if (!mat)
        return NULL;
    for (i = 0; i < n; ++i) {
        int orig_i = get_index(names, sorted->items[i]);
        dist = single_source_distances(fg, orig_i);
        if (!dist) {
            free(mat);
            return NULL;
        }
        for (j = 0; j < n; ++j) {
            int orig_j = get_index(names, sorted->items[j]);
            int d = dist[orig_j];
            if (i == j)
                mat[i * n + j] = 0;
            else if (d != -1 && d <= limit)
                mat[i * n + j] = d;
            else
                mat[i * n + j] = 0;
        }
        free(dist);
        (void)si;
        (void)sj;
    }
    return mat;
}

static bool has_edge_to(const graph_t *g, int u, int v)
{
    int i = 0;

    for (i = 0; i < g->deg[u]; ++i) {
        if (g->adj[u][i] == v)
            return true;
    }
    return false;
}

typedef struct chain_s {
    int *nodes;
    int len;
} chain_t;

static int cmp_chain(const void *a, const void *b, void *data)
{
    const chain_t *ca = a;
    const chain_t *cb = b;
    const name_list_t *names = data;
    int i = 0;

    if (ca->len != cb->len)
        return ca->len - cb->len;
    for (i = 0; i < ca->len && i < cb->len; ++i) {
        int ia = ca->nodes[i];
        int ib = cb->nodes[i];
        int c = gos_strcmp(names->items[ia], names->items[ib]);
        if (c != 0)
            return c;
    }
    return 0;
}

int run_plots_mode(const char *fr, const char *cr, int n)
{
    name_list_t names;
    name_list_t sorted;
    edges_t fedges;
    edges_t cedges;
    graph_t *fg = NULL;
    graph_t *cg = NULL;
    int *mat = NULL;
    int queen = -1;
    int *distq = NULL;
    bool *direct = NULL;
    int i = 0;
    int j = 0;
    chain_t *chains = NULL;
    int chain_count = 0;
    int fail_count = 0;

    if (!parse_friendships(fr, &names, &fedges))
        return GOS_EXIT_ERROR;
    sorted = sorted_names_copy(&names);
    if (sorted.size == 0)
        return GOS_EXIT_ERROR;
    fg = graph_build_undirected(names.size, &fedges);
    if (!fg)
        return GOS_EXIT_ERROR;
    mat = build_matrix(fg, &names, &sorted, n);
    if (!mat)
        return GOS_EXIT_ERROR;
    print_names(&sorted);
    print_matrix(mat, sorted.size);
    free(mat);
    if (!parse_conspiracies(cr, &names, &cedges))
        return GOS_EXIT_ERROR;
    cg = graph_build_directed(names.size, &cedges);
    if (!cg)
        return GOS_EXIT_ERROR;
    queen = get_index(&names, "Cersei Lannister");
    if (queen < 0)
        return GOS_EXIT_ERROR;
    distq = single_source_distances(fg, queen);
    if (!distq)
        return GOS_EXIT_ERROR;
    direct = calloc(names.size, sizeof(bool));
    if (!direct)
        return GOS_EXIT_ERROR;
    for (i = 0; (size_t)i < names.size; ++i)
        direct[i] = false;
    for (i = 0; (size_t)i < names.size; ++i)
        if (has_edge_to(cg, i, queen))
            direct[i] = true;
    fprintf(stdout, "Conspiracies:\n");
    chains = malloc(sizeof(chain_t) * names.size);
    if (!chains)
        return GOS_EXIT_ERROR;
    for (i = 0; (size_t)i < names.size; ++i) {
        if (!direct[i])
            continue;
        {
            int *path = malloc(sizeof(int) * (int)names.size);
            int len = 0;
            bool ok = false;
            ok = find_chain(cg, distq, direct, queen, n, i, path, &len,
                &names);
            if (ok && len >= 2) {
                chains[chain_count].nodes = path;
                chains[chain_count].len = len;
                chain_count += 1;
            } else {
                free(path);
                fprintf(stdout, "No conspiracy possible against %s\n",
                    names.items[i]);
                fail_count += 1;
            }
        }
    }
    /* simple insertion sort to keep C89 compat */
    for (i = 1; i < chain_count; ++i) {
        chain_t key = chains[i];
        j = i - 1;
        while (j >= 0 && cmp_chain(&chains[j], &key, &names) > 0) {
            chains[j + 1] = chains[j];
            j -= 1;
        }
        chains[j + 1] = key;
    }
    for (i = 0; i < chain_count; ++i) {
        print_chain(chains[i].nodes, chains[i].len, &names);
        free(chains[i].nodes);
    }
    free(chains);
    if (fail_count == 0)
        fprintf(stdout, "Result:\nThe stone is safe!\n");
    else
        fprintf(stdout, "Result:\nThere is only one way out: treason!\n");
    free(distq);
    free(direct);
    graph_destroy(fg);
    graph_destroy(cg);
    free(fedges.items);
    free(cedges.items);
    free(sorted.items);
    free(names.items);
    return 0;
}

