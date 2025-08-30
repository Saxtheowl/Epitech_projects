/*
** EPITECH PROJECT, 2025
** InfinAdd_roro
** File description:
** Main
*/

#include <stdio.h>
#include <stdlib.h>
#include "infin_add.h"

int main(int ac, char **av)
{
    char *res;

    if (ac != 3)
        return ERR_CODE;
    res = infin_add(av[1], av[2]);
    if (res == NULL)
        return ERR_CODE;
    printf("%s\n", res);
    free(res);
    return 0;
}
