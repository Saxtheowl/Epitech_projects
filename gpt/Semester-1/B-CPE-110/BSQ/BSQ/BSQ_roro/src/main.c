/*
** EPITECH PROJECT, 2025
** BSQ_roro
** File description:
** Main
*/

#include <stdio.h>
#include "bsq.h"

static int run(const char *path)
{
    map_t map;
    int st;

    st = load_map(path, &map);
    if (st != 0)
        return ERR_CODE;
    if (validate_map(&map) != 0) {
        free_map(&map);
        return ERR_CODE;
    }
    solve_bsq(&map);
    print_map(&map);
    free_map(&map);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return ERR_CODE;
    return run(av[1]);
}
