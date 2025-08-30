/*
** EPITECH PROJECT, 2024
** base_conversion.c
** File description:
** base conversion functions for bistromatic
*/

#include <stdlib.h>
#include "../include/bistromatic.h"

int get_digit_value(char const *base, char c)
{
    int i = 0;

    if (base == NULL)
        return -1;
    while (base[i]) {
        if (base[i] == c)
            return i;
        i++;
    }
    return -1;
}

char get_char_from_value(char const *base, int value)
{
    int base_len = my_strlen(base);

    if (base == NULL || value < 0 || value >= base_len)
        return '\0';
    return base[value];
}

char *convert_to_decimal(char const *base, char const *num)
{
    return my_strdup(num);
}