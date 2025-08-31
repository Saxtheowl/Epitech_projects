/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Input parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "gos.h"

static void names_init(name_list_t *n)
{
    n->items = NULL;
    n->size = 0;
    n->cap = 0;
}

static void edges_init(edges_t *e)
{
    e->items = NULL;
    e->size = 0;
    e->cap = 0;
}

static bool names_push(name_list_t *n, const char *name)
{
    char *copy = NULL;
    char **tmp = NULL;

    copy = gos_strdup(name);
    if (!copy)
        return false;
    if (n->size == n->cap) {
        size_t new_cap = (n->cap == 0) ? 8 : n->cap * 2;
        tmp = realloc(n->items, new_cap * sizeof(char *));
        if (!tmp) {
            free(copy);
            return false;
        }
        n->items = tmp;
        n->cap = new_cap;
    }
    n->items[n->size++] = copy;
    return true;
}

static bool edges_push(edges_t *e, int from, int to)
{
    edge_t *tmp = NULL;

    if (e->size == e->cap) {
        size_t new_cap = (e->cap == 0) ? 16 : e->cap * 2;
        tmp = realloc(e->items, new_cap * sizeof(edge_t));
        if (!tmp)
            return false;
        e->items = tmp;
        e->cap = new_cap;
    }
    e->items[e->size].from = from;
    e->items[e->size].to = to;
    e->size++;
    return true;
}

static char *extract_between(const char *s, const char *a, const char *b)
{
    const char *pa = strstr(s, a);
    const char *pb = NULL;
    size_t len = 0;

    if (!pa)
        return NULL;
    pa += strlen(a);
    pb = strstr(pa, b);
    if (!pb)
        return NULL;
    len = (size_t)(pb - pa);
    return gos_strndup(pa, len);
}

int name_index(name_list_t *names, const char *name)
{
    size_t i = 0;

    for (i = 0; i < names->size; ++i) {
        if (gos_strcmp(names->items[i], name) == 0)
            return (int)i;
    }
    if (!names_push(names, name))
        return -1;
    return (int)(names->size - 1);
}

static int find_existing_index(const name_list_t *names, const char *name)
{
    size_t i = 0;

    for (i = 0; i < names->size; ++i) {
        if (gos_strcmp(names->items[i], name) == 0)
            return (int)i;
    }
    return -1;
}

static int cmp_strptr(const void *a, const void *b)
{
    const char *const *sa = (const char *const *)a;
    const char *const *sb = (const char *const *)b;
    return gos_strcmp(*sa, *sb);
}

void names_sort(name_list_t *names)
{
    qsort(names->items, names->size, sizeof(char *), cmp_strptr);
}

bool parse_friendships(const char *path, name_list_t *names, edges_t *edges)
{
    FILE *f = NULL;
    char buf[1024];
    char *a = NULL;
    char *b = NULL;
    int ia = 0;
    int ib = 0;

    names_init(names);
    edges_init(edges);
    f = fopen(path, "r");
    if (!f)
        return false;
    while (fgets(buf, sizeof(buf), f)) {
        a = extract_between(buf, "", " is friends with ");
        b = NULL;
        if (a)
            b = gos_strdup(strstr(buf, " is friends with ") + 17);
        if (!a || !b) {
            free(a);
            free(b);
            continue;
        }
        a = gos_trim(a);
        b = gos_trim(b);
        ia = name_index(names, a);
        ib = name_index(names, b);
        if (ia < 0 || ib < 0) {
            free(a);
            free(b);
            fclose(f);
            return false;
        }
        if (!edges_push(edges, ia, ib) || !edges_push(edges, ib, ia)) {
            free(a);
            free(b);
            fclose(f);
            return false;
        }
        free(a);
        free(b);
    }
    fclose(f);
    return true;
}

bool parse_conspiracies(const char *path, const name_list_t *names,
    edges_t *edges)
{
    FILE *f = NULL;
    char buf[1024];
    char *a = NULL;
    char *b = NULL;
    int ia = 0;
    int ib = 0;

    edges_init(edges);
    f = fopen(path, "r");
    if (!f)
        return false;
    while (fgets(buf, sizeof(buf), f)) {
        a = extract_between(buf, "", " is plotting against ");
        b = NULL;
        if (a)
            b = gos_strdup(strstr(buf, " is plotting against ") + 21);
        if (!a || !b) {
            free(a);
            free(b);
            continue;
        }
        a = gos_trim(a);
        b = gos_trim(b);
        ia = find_existing_index(names, a);
        ib = find_existing_index(names, b);
        if (ia < 0 || ib < 0) {
            free(a);
            free(b);
            fclose(f);
            return false;
        }
        if (!edges_push(edges, ia, ib)) {
            free(a);
            free(b);
            fclose(f);
            return false;
        }
        free(a);
        free(b);
    }
    fclose(f);
    return true;
}

int get_index(const name_list_t *names, const char *name)
{
    size_t i = 0;

    for (i = 0; i < names->size; ++i) {
        if (gos_strcmp(names->items[i], name) == 0)
            return (int)i;
    }
    return -1;
}
