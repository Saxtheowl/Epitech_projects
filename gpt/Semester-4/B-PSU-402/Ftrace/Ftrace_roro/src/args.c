/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   args parsing
*/

#include <stdio.h>
#include "ftrace.h"

void print_usage(void)
{
    printf("USAGE: ftrace <command>\n");
}

int parse_args(int ac, char **av, traced_t *t)
{
    if (ac == 2 && my_strcmp(av[1], "--help") == 0) {
        print_usage();
        return 1; /* signal: help printed */
    }
    if (ac < 2) {
        print_usage();
        return -1;
    }
    t->prog = av[1];
    t->argv = &av[1];
    t->main_addr = 0;
    return 0;
}
