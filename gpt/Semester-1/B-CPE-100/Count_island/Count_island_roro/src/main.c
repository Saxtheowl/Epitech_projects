/*
** EPITECH PROJECT, 2025
** Count_island_roro
** File description:
** Main entry point
*/

#include <stdio.h>
#include "count_island.h"

static int run(const char *path)
{
    map_t map;
    int status;

    status = load_map(path, &map);
    if (status != 0)
        return ERR_CODE;
    if (validate_map(&map) != 0) {
        free_map(&map);
        return ERR_CODE;
    }
    label_islands(&map);
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

