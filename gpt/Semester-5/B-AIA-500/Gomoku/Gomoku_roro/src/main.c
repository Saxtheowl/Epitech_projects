/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Entry point and REPL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gomoku.h"

static int repl(gomoku_t *g)
{
    char *line;
    size_t cap;
    ssize_t rd;

    line = NULL;
    cap = 0;
    while ((rd = getline(&line, &cap, stdin)) != -1) {
        if (rd > 0 && line[rd - 1] == '\n')
            line[rd - 1] = '\0';
        if (handle_line(g, line) != 0)
            break;
        fflush(stdout);
    }
    free(line);
    return 0;
}

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./gomoku_roro [options]\n");
    printf("DESCRIPTION\n");
    printf("    Protocol-compatible Gomoku AI (basic).\n");
}

int gomoku_main(int ac, char **av)
{
    gomoku_t g;

    (void)av;
    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    if (board_init(&g, 20) != 0)
        return 84;
    repl(&g);
    board_free(&g);
    return 0;
}

int main(int ac, char **av)
{
    return gomoku_main(ac, av);
}
