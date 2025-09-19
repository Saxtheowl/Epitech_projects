/*
** EPITECH PROJECT, 2025
** Mini Printf Bootstrap
** File description:
** Sum numbers using va_args
*/

#include "includes/bsprintf.h"

int sum_numbers(int n, ...)
{
    va_list args;
    int sum = 0;
    int i;

    va_start(args, n);
    for (i = 0; i < n; i++) {
        sum += va_arg(args, int);
    }
    va_end(args);

    return sum;
}