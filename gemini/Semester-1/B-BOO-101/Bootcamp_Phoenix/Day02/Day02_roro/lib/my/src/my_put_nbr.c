/*
** EPITECH PROJECT, 2025
** Day02_roro
** File description:
** my_put_nbr
*/

#include "my.h"

void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
}
