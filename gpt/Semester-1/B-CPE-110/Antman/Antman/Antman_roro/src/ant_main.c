/*
** EPITECH PROJECT, 2025
** Antman_roro
** File description:
** antman main
*/

#include "antman.h"

int main(int ac, char **av)
{
    if (ac != 2)
        return ERR_CODE;
    return antman(av[1]);
}
