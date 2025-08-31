/*
** EPITECH PROJECT, 2025
** Groundhog_roro
** File description:
** args
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "groundhog.h"

void print_help(void)
{
    printf("SYNOPSIS\n");
    printf("./groundhog period\n");
    printf("DESCRIPTION\n");
    printf("period the number of days defining a period\n");
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

int parse_args(int ac, char const **av, int *period)
{
    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        print_help();
        return -1;
    }
    if (ac != 2 || !is_number(av[1]))
        return 84;
    *period = atoi(av[1]);
    if (*period <= 0)
        return 84;
    return 0;
}

