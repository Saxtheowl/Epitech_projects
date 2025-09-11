/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** show_params.c
*/

#include "../includes/phoenix.h"

int main(int argc, char **argv)
{
    int i = 0;

    while (i < argc) {
        show_string(argv[i]);
        my_putchar('\n');
        i++;
    }

    return 0;
}