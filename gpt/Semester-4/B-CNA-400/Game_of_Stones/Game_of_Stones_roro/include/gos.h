/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** header
*/

#ifndef GOS_H
    #define GOS_H

    #include <stddef.h>
    #include <stdbool.h>

    #define crown_name "Cersei Lannister"

    typedef struct graph_s {
        char **names;
        size_t count;
        size_t cap;
        int **adj;      /* undirected FR adjacency (0/1) */
        int **dist;     /* all-pairs distances (FR) */
        int **cr_out;   /* CR directed edges out */
        int **cr_in;    /* CR directed edges in (reverse) */
    } graph_t;

    /* parse */
    int cmd_main(int ac, char const **av);
    void print_usage(void);
    void print_help(void);

    /* fr/cr */
    int load_fr(const char *path, graph_t *g);
    int load_cr(const char *path, graph_t *g);
    void free_graph(graph_t *g);

    /* graph */
    int ensure_name(graph_t *g, const char *name);
    int name_index(const graph_t *g, const char *name);
    void compute_all_pairs(graph_t *g);
    int bfs_distance(const graph_t *g, int a, int b);

    /* modes */
    int run_links(graph_t *g, const char *p1, const char *p2);
    int run_plots(graph_t *g, const char *cr, int n);

    /* utils */
    char *str_dup(const char *s);
    char *str_trim(char *s);
    bool starts_with(const char *s, const char *prefix);
    void *xcalloc(size_t nmemb, size_t size);
    void *xrealloc(void *ptr, size_t size);

#endif /* GOS_H */
