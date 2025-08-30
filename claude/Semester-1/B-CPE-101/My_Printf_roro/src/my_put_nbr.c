/*
** EPITECH PROJECT, 2024
** my_put_nbr.c
** File description:
** writes an integer to standard output
*/

#include "../include/my.h"

int my_put_nbr(int nb)
{
    int count = 0;

    if (nb < 0) {
        my_putchar('-');
        count++;
        if (nb == -2147483648) {
            my_putstr("2147483648");
            return count + 10;
        }
        nb = -nb;
    }
    if (nb >= 10) {
        count += my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
    return count + 1;
}