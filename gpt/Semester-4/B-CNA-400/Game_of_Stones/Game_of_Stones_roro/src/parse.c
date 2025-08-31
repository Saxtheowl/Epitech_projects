/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** parse args and dispatch
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gos.h"

void print_help(void)
{
    printf("USAGE\n");
    printf("./game_of_stones [ -- links FR P1 P2 | -- plots FR CR n]\n");
    printf("DESCRIPTION\n");
    printf("FR file containing friendship relations between people\n");
    printf("Pi name of someone in the friendships file\n");
    printf("CR file containing conspiracies intentions\n");
    printf("n maximum length of friendship paths\n");
}

void print_usage(void)
{
    fprintf(stderr, "USAGE\n");
    fprintf(stderr, "./game_of_stones [ -- links FR P1 P2 | -- plots FR CR n]\n");
    fprintf(stderr, "DESCRIPTION\n");
    fprintf(stderr, "FR file containing friendship relations between people\n");
    fprintf(stderr, "Pi name of someone in the friendships file\n");
    fprintf(stderr, "CR file containing conspiracies intentions\n");
    fprintf(stderr, "n maximum length of friendship paths\n");
}

static bool is_number(const char *s)
{
    size_t i;

    if (!s || *s == '\0')
        return false;
    for (i = 0; s[i]; ++i)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

static int mode_links(const char *fr, const char *p1, const char *p2)
{
    graph_t g;

    if (load_fr(fr, &g) != 0)
        return 84;
    compute_all_pairs(&g);
    run_links(&g, p1, p2);
    free_graph(&g);
    return 0;
}

static int mode_plots(const char *fr, const char *cr, const char *ns)
{
    int n;
    graph_t g;

    if (!is_number(ns))
        return 84;
    n = atoi(ns);
    if (n < 0)
        return 84;
    if (load_fr(fr, &g) != 0)
        return 84;
    if (run_plots(&g, cr, n) != 0) {
        free_graph(&g);
        return 84;
    }
    free_graph(&g);
    return 0;
}

int cmd_main(int ac, char const **av)
{
    if (ac == 2 && (strcmp(av[1], "-- help") == 0 || strcmp(av[1], "--help") == 0)) {
        print_help();
        return 0;
    }
    if ((ac == 6 && strcmp(av[1], "--") == 0 && strcmp(av[2], "links") == 0)
        || (ac == 5 && strcmp(av[1], "--links") == 0))
        return mode_links(av[ac - 3], av[ac - 2], av[ac - 1]);
    if ((ac == 6 && strcmp(av[1], "--") == 0 && strcmp(av[2], "plots") == 0)
        || (ac == 5 && strcmp(av[1], "--plots") == 0))
        return mode_plots(av[ac - 3], av[ac - 2], av[ac - 1]);
    return 84;
}
