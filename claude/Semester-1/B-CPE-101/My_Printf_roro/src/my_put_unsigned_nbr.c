/*
** EPITECH PROJECT, 2024
** my_put_unsigned_nbr.c
** File description:
** writes an unsigned integer to standard output
*/

#include "../include/my.h"

int my_put_unsigned_nbr(unsigned int nb)
{
    int count = 0;

    if (nb >= 10) {
        count += my_put_unsigned_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
    return count + 1;
}