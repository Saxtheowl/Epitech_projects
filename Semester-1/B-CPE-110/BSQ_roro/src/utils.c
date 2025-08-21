/*
** EPITECH PROJECT, 2024
** BSQ
** File description:
** Utility functions
*/

#include "../include/bsq.h"

size_t get_min(size_t a, size_t b, size_t c)
{
    size_t min_val = a;

    if (b < min_val)
        min_val = b;
    if (c < min_val)
        min_val = c;

    return min_val;
}

size_t my_strlen(const char *str)
{
    size_t len = 0;

    if (!str)
        return 0;

    while (str[len])
        len++;

    return len;
}

int my_atoi(const char *str)
{
    int result = 0;
    size_t i = 0;

    if (!str)
        return 0;

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(const char *str)
{
    if (str)
        write(1, str, my_strlen(str));
}