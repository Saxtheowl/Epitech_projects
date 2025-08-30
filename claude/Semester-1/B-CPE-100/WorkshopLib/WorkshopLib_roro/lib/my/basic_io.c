/*
** EPITECH PROJECT, 2024
** basic_io.c
** File description:
** basic input/output functions
*/

#include <unistd.h>
#include "../../include/my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

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

int my_putstr(char const *str)
{
    int length = 0;

    if (str == NULL)
        return -1;
    while (str[length] != '\0') {
        my_putchar(str[length]);
        length++;
    }
    return length;
}

int my_isneg(int nb)
{
    if (nb < 0) {
        my_putchar('N');
    } else {
        my_putchar('P');
    }
    return 0;
}