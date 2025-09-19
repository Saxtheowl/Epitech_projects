/*
** EPITECH PROJECT, 2025
** Mini Printf Bootstrap
** File description:
** Sum string lengths using va_args
*/

#include "includes/bsprintf.h"

static int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int sum_strings_length(int n, ...)
{
    va_list args;
    int total_length = 0;
    char *str;
    int i;

    va_start(args, n);
    for (i = 0; i < n; i++) {
        str = va_arg(args, char *);
        total_length += my_strlen(str);
    }
    va_end(args);

    return total_length;
}