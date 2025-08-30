/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** utility functions for bistromatic
*/

#include <unistd.h>
#include <stdlib.h>
#include "../include/bistromatic.h"

void my_putstr(char const *str)
{
    if (str == NULL)
        return;
    while (*str) {
        write(1, str, 1);
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