/*
** EPITECH PROJECT, 2025
** MyLs_roro
** File description:
** Main
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_ls.h"

int main(int ac, char **av)
{
    flags_t f;
    int idx;
    int i;
    int ret;

    ret = parse_flags(ac, av, &idx, &f);
    if (ret != 0)
        return ERR_CODE;
    if (idx >= ac)
        return my_ls_path(".", &f, 0);
    for (i = idx; i < ac; ++i) {
        int head = (ac - idx > 1) ? 1 : 0;
        if (my_ls_path(av[i], &f, head) != 0)
            ret = ERR_CODE;
        if (i + 1 < ac)
            printf("\n");
    }
    return ret;
}
