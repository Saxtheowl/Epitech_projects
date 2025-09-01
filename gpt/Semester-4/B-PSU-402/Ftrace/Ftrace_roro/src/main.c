/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
**   entry point
*/

#include <stdio.h>
#include "ftrace.h"

int main(int ac, char **av)
{
    traced_t t;
    int r = parse_args(ac, av, &t);
    if (r == 1)
        return 0; /* --help */
    if (r != 0)
        return EXIT_ERR;
    if (run_trace(&t) != 0)
        return EXIT_ERR;
    return 0;
}
