/*
** EPITECH PROJECT, 2025
** MatchNmatch_roro
** File description:
** Main CLI wrapper
*/

#include <stdio.h>
#include "matchnmatch.h"

int main(int ac, char **av)
{
    int m;
    int n;

    if (ac != 3)
        return ERR_CODE;
    m = match(av[1], av[2]);
    n = nmatch(av[1], av[2]);
    printf("%d\n%d\n", m, n);
    return 0;
}
