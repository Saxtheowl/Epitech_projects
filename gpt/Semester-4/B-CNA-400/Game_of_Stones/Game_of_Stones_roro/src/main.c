/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "gos.h"

int main(int ac, char const **av)
{
    int st;

    st = cmd_main(ac, av);
    if (st == 84) {
        print_usage();
        return 84;
    }
    return st;
}
