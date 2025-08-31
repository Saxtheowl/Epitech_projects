/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   Public interfaces
*/

#ifndef GOS_H
#define GOS_H

#include <stddef.h>
#include <stdbool.h>

#define GOS_EXIT_ERROR 84

typedef struct name_list_s {
    char **items;
    size_t size;
    size_t cap;
} name_list_t;

typedef struct edge_s {
    int from;
    int to;
} edge_t;

typedef struct edges_s {
    edge_t *items;
    size_t size;
    size_t cap;
} edges_t;

typedef struct graph_s {
    int **adj;
    int *deg;
    size_t n;
} graph_t;

/* strings.c */
int gos_strcmp(const char *a, const char *b);
size_t gos_strlen(const char *s);
char *gos_strdup(const char *s);
char *gos_strndup(const char *s, size_t n);
void gos_free_array(char **arr, size_t n);
char *gos_trim(char *s);

/* parser.c */
bool parse_friendships(const char *path, name_list_t *names, edges_t *edges);
bool parse_conspiracies(const char *path, const name_list_t *names, edges_t *edges);
int name_index(name_list_t *names, const char *name);
void names_sort(name_list_t *names);
int get_index(const name_list_t *names, const char *name);

/* graph.c */
graph_t *graph_build_directed(size_t n, const edges_t *edges);
graph_t *graph_build_undirected(size_t n, const edges_t *edges);
void graph_destroy(graph_t *g);
int bfs_distance(const graph_t *g, int src, int dst);
int *all_pairs_distances_n(const graph_t *g, int limit);
int *single_source_distances(const graph_t *g, int src);
bool find_chain(const graph_t *cr, const int *dist_to_queen, const bool *is_direct_enemy,
    int queen_idx, int n, int target, int *out_path, int *out_len, const name_list_t *names);

/* links_mode.c */
int run_links_mode(const char *fr, const char *p1, const char *p2);

/* plots_mode.c */
int run_plots_mode(const char *fr, const char *cr, int n);

/* output.c */
void print_usage(void);
void print_names(const name_list_t *names);
void print_matrix(const int *mat, size_t n);
void print_chain(const int *path, int len, const name_list_t *names);

#endif /* GOS_H */
