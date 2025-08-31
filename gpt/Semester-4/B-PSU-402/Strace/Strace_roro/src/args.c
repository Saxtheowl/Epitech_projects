/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** args
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "strace.h"

static void print_help(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
}

void print_usage(void)
{
    fprintf(stderr, "USAGE: ./strace [-s] [-p <pid>|<command>]\n");
}

static int is_number(const char *s)
{
    size_t i;

    if (!s || *s == '\0')
        return 0;
    for (i = 0; s[i]; ++i)
        if (!isdigit((unsigned char)s[i]))
            return 0;
    return 1;
}

int parse_args(int ac, char const **av, options_t *opt)
{
    int i;

    opt->opt_s = false;
    opt->pid = -1;
    opt->cmd = NULL;
    if (ac < 2)
        return 84;
    i = 1;
    if (strcmp(av[i], "--help") == 0) {
        print_help();
        return -1;
    }
    if (strcmp(av[i], "-s") == 0) {
        opt->opt_s = true;
        i += 1;
    }
    if (i >= ac)
        return 84;
    if (strcmp(av[i], "-p") == 0) {
        if (i + 1 >= ac || !is_number(av[i + 1]))
            return 84;
        opt->pid = (pid_t)atoi(av[i + 1]);
        i += 2;
        if (i != ac)
            return 84;
        return 0;
    }
    opt->cmd = &av[i];
    return 0;
}
