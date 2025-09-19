/*
** EPITECH PROJECT, 2025
** Mini Printf Bootstrap
** File description:
** Display arguments using va_args based on format string
*/

#include "includes/bsprintf.h"
#include <unistd.h>

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static void my_putstr(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

static void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
    }
    my_putchar((nb % 10) + '0');
}

void disp_stdarg(char *s, ...)
{
    va_list args;
    int i = 0;

    if (!s)
        return;

    va_start(args, s);
    while (s[i]) {
        if (s[i] == 'c') {
            my_putchar(va_arg(args, int));
            my_putchar('\n');
        } else if (s[i] == 's') {
            my_putstr(va_arg(args, char *));
            my_putchar('\n');
        } else if (s[i] == 'i') {
            my_putnbr(va_arg(args, int));
            my_putchar('\n');
        }
        i++;
    }
    va_end(args);
}