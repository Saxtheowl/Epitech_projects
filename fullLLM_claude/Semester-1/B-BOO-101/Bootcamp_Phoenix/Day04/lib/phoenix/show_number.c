/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** show_number.c
*/

#include <unistd.h>

void my_putchar(char c);

static void show_positive_number(int nb)
{
    if (nb >= 10)
        show_positive_number(nb / 10);
    my_putchar((nb % 10) + '0');
}

int show_number(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        show_positive_number(-nb);
    } else {
        show_positive_number(nb);
    }
    return 0;
}