/*
** EPITECH PROJECT, 2024
** libmy
** File description:
** puts a number on the standard output
*/

#include "../../include/my.h"

int my_putnbr(int nb)
{
    int divisor = 1;

    if (nb < 0) {
        my_putchar('-');
        if (nb == -2147483648) {
            my_putstr("2147483648");
            return 0;
        }
        nb = -nb;
    }
    
    while (nb / divisor >= 10)
        divisor *= 10;
    
    while (divisor > 0) {
        my_putchar((nb / divisor) % 10 + '0');
        divisor /= 10;
    }
    return 0;
}