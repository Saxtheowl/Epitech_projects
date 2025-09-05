/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Utility functions for anagram
*/

#include "anagram.h"

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}