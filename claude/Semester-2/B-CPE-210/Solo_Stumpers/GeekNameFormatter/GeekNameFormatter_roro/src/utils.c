/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Utility functions for geek name formatter
*/

#include "geek_name_formatter.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i]) {
        my_putchar(str[i]);
        i++;
    }
}

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

char replace_geek_char(char c)
{
    if (c == 'o' || c == 'O')
        return '0';
    if (c == 'i' || c == 'I')
        return '1';
    if (c == 'u' || c == 'U')
        return '2';
    if (c == 'e' || c == 'E')
        return '3';
    if (c == 'a' || c == 'A')
        return '4';
    if (c == 'y' || c == 'Y')
        return '5';
    return c;
}