/*
** EPITECH PROJECT, 2025
** Rush2_roro
** File description:
** step04: decode substitution
*/

#include "rush2.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return ERR_CODE;
    return step04_main(av[1]);
}
