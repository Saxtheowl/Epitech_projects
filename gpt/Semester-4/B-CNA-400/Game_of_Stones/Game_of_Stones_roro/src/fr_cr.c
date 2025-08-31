/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** FR/CR parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gos.h"

static void ensure_matrix(graph_t *g)
{
    size_t i;
    size_t j;
    size_t old;
    int **new_adj;
    int **new_out;
    int **new_in;

    if (g->cap >= g->count)
        return;
    old = g->cap;
    if (g->cap == 0)
        g->cap = g->count;
    else
        g->cap = g->count;
    new_adj = (int **)xcalloc(g->cap, sizeof(int *));
    new_out = (int **)xcalloc(g->cap, sizeof(int *));
    new_in = (int **)xcalloc(g->cap, sizeof(int *));
    for (i = 0; i < g->cap; ++i) {
        new_adj[i] = (int *)xcalloc(g->cap, sizeof(int));
        new_out[i] = (int *)xcalloc(g->cap, sizeof(int));
        new_in[i] = (int *)xcalloc(g->cap, sizeof(int));
    }
    if (g->adj) {
        for (i = 0; i < old; ++i)
            for (j = 0; j < old; ++j) {
                new_adj[i][j] = g->adj[i][j];
                new_out[i][j] = g->cr_out[i][j];
                new_in[i][j] = g->cr_in[i][j];
            }
        for (i = 0; i < old; ++i) {
            free(g->adj[i]);
            free(g->cr_out[i]);
            free(g->cr_in[i]);
        }
        free(g->adj);
        free(g->cr_out);
        free(g->cr_in);
    }
    g->adj = new_adj;
    g->cr_out = new_out;
    g->cr_in = new_in;
}

int ensure_name(graph_t *g, const char *name)
{
    size_t i;
    char **nn;

    for (i = 0; i < g->count; ++i)
        if (strcmp(g->names[i], name) == 0)
            return (int)i;
    nn = (char **)xrealloc(g->names, sizeof(char *) * (g->count + 1));
    g->names = nn;
    g->names[g->count] = str_dup(name);
    g->count += 1;
    return (int)(g->count - 1);
}

int name_index(const graph_t *g, const char *name)
{
    size_t i;

    for (i = 0; i < g->count; ++i)
        if (strcmp(g->names[i], name) == 0)
            return (int)i;
    return -1;
}

/* no compare helper needed */

static int finalize_fr(graph_t *g)
{
    if (g->count == 0)
        return 84;
    ensure_matrix(g);
    return 0;
}

static int parse_fr_line(graph_t *g, char *line)
{
    const char *sep = " is friends with ";
    char *p;
    char *a;
    char *b;
    int ia;
    int ib;

    p = strstr(line, sep);
    if (!p)
        return 0;
    *p = '\0';
    a = str_trim(line);
    b = str_trim(p + strlen(sep));
    if (*a == '\0' || *b == '\0')
        return 0;
    ia = ensure_name(g, a);
    ib = ensure_name(g, b);
    ensure_matrix(g);
    g->adj[ia][ib] = 1;
    g->adj[ib][ia] = 1;
    return 1;
}

int load_fr(const char *path, graph_t *g)
{
    FILE *f;
    char *line;
    size_t cap;
    (void)cap; /* silence unused warnings in some libc */
    /* len var unused intentionally */
    int any;

    g->names = NULL;
    g->count = 0;
    g->adj = NULL;
    g->dist = NULL;
    g->cr_out = NULL;
    g->cr_in = NULL;
    g->cap = 0;
    f = fopen(path, "r");
    if (!f)
        return 84;
    cap = 0;
    line = NULL;
    any = 0;
    while (getline(&line, &cap, f) != -1) {
        str_trim(line);
        if (*line == '\0')
            continue;
        any += parse_fr_line(g, line);
    }
    free(line);
    fclose(f);
    if (any == 0)
        return 84;
    return finalize_fr(g);
}

static int parse_cr_line(graph_t *g, char *line)
{
    const char *sep = " is plotting against ";
    char *p;
    char *a;
    char *b;
    int ia;
    int ib;

    p = strstr(line, sep);
    if (!p)
        return 0;
    *p = '\0';
    a = str_trim(line);
    b = str_trim(p + strlen(sep));
    if (*a == '\0' || *b == '\0')
        return 0;
    ia = name_index(g, a);
    ib = name_index(g, b);
    if (ia < 0 || ib < 0)
        return -1;
    g->cr_out[ia][ib] = 1;
    g->cr_in[ib][ia] = 1;
    return 1;
}

int load_cr(const char *path, graph_t *g)
{
    FILE *f;
    char *line;
    size_t cap;
    int st;

    f = fopen(path, "r");
    if (!f)
        return 84;
    cap = 0;
    line = NULL;
    while (getline(&line, &cap, f) != -1) {
        str_trim(line);
        if (*line == '\0')
            continue;
        st = parse_cr_line(g, line);
        if (st < 0) {
            free(line);
            fclose(f);
            return 84;
        }
    }
    free(line);
    fclose(f);
    return 0;
}

void free_graph(graph_t *g)
{
    size_t i;

    if (!g)
        return;
    if (g->names) {
        for (i = 0; i < g->count; ++i)
            free(g->names[i]);
        free(g->names);
    }
    if (g->adj) {
        for (i = 0; i < g->count; ++i)
            free(g->adj[i]);
        free(g->adj);
    }
    if (g->cr_out) {
        for (i = 0; i < g->count; ++i)
            free(g->cr_out[i]);
        free(g->cr_out);
    }
    if (g->cr_in) {
        for (i = 0; i < g->count; ++i)
            free(g->cr_in[i]);
        free(g->cr_in);
    }
    if (g->dist) {
        for (i = 0; i < g->count; ++i)
            free(g->dist[i]);
        free(g->dist);
    }
    memset(g, 0, sizeof(*g));
}
