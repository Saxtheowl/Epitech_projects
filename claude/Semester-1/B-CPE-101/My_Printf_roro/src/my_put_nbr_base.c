/*
** EPITECH PROJECT, 2024
** my_put_nbr_base.c
** File description:
** writes a number in a given base
*/

#include "../include/my.h"

int my_put_nbr_base(int nbr, char const *base)
{
    int base_len = my_strlen(base);
    int count = 0;

    if (base == NULL || base_len < 2)
        return 0;
    if (nbr < 0) {
        my_putchar('-');
        count++;
        if (nbr == -2147483648) {
            my_put_nbr_base(2147483648 / base_len, base);
            my_putchar(base[2147483648 % base_len]);
            return count + 11;
        }
        nbr = -nbr;
    }
    if (nbr >= base_len) {
        count += my_put_nbr_base(nbr / base_len, base);
    }
    my_putchar(base[nbr % base_len]);
    return count + 1;
}

int my_put_unsigned_nbr_base(unsigned int nbr, char const *base)
{
    unsigned int base_len = my_strlen(base);
    int count = 0;

    if (base == NULL || base_len < 2)
        return 0;
    if (nbr >= base_len) {
        count += my_put_unsigned_nbr_base(nbr / base_len, base);
    }
    my_putchar(base[nbr % base_len]);
    return count + 1;
}