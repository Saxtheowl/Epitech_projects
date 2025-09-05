/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Utility functions for sort_words
*/

#include "sort_words.h"

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

int my_strcasecmp(char const *s1, char const *s2)
{
    int i = 0;

    if (!s1 || !s2)
        return 0;
    while (s1[i] && s2[i]) {
        if (to_lower(s1[i]) != to_lower(s2[i]))
            return to_lower(s1[i]) - to_lower(s2[i]);
        i++;
    }
    return to_lower(s1[i]) - to_lower(s2[i]);
}