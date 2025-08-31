/*
** EPITECH PROJECT, 2025
** Strace_roro
** File description:
** main
*/

#include <stdio.h>
#include "strace.h"

static int invalid(void)
{
    return 84;
}

int main(int ac, char const **av)
{
    options_t opt;
    int st;

    st = parse_args(ac, av, &opt);
    if (st < 0)
        return 0;
    if (st == 84)
        return invalid();
    if (opt.pid != -1)
        return trace_attach(&opt);
    return trace_exec(&opt);
}

