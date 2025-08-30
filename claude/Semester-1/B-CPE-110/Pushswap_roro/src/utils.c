/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** Utility functions for Push Swap
*/

#include <unistd.h>
#include "../include/push_swap.h"

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

int my_atoi(char const *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str == NULL)
        return 0;
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    } else if (str[0] == '+') {
        i = 1;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

int is_valid_number(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 0;
    if (str[0] == '-' || str[0] == '+')
        i = 1;
    if (str[i] == '\0')
        return 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}