/*
** EPITECH PROJECT, 2025
** Star_roro
** File description:
** Main
*/

#include <stdio.h>
#include <stdlib.h>
#include "star.h"

static int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (s == NULL || out == NULL)
        return -1;
    v = strtol(s, &end, 10);
    if (end == s || *end != '\0' || v < 0 || v > 10000)
        return -1;
    *out = (int)v;
    return 0;
}

int main(int ac, char **av)
{
    int size;

    if (ac != 2)
        return ERR_CODE;
    if (parse_int(av[1], &size) != 0)
        return ERR_CODE;
    if (print_star(size) != 0)
        return ERR_CODE;
    return 0;
}
