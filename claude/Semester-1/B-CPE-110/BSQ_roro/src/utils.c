/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** Utility functions for BSQ
*/

#include <unistd.h>
#include "../include/bsq.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    if (str == NULL)
        return;
    while (*str) {
        my_putchar(*str);
        str++;
    }
}

int my_strlen(char const *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(char const *str)
{
    int result = 0;
    int i = 0;

    if (str == NULL)
        return 0;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}