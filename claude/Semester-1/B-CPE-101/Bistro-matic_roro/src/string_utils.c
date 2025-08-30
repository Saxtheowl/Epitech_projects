/*
** EPITECH PROJECT, 2024
** string_utils.c
** File description:
** string utility functions for bistromatic
*/

#include <stdlib.h>
#include "../include/bistromatic.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *dup = malloc(len + 1);
    int i = 0;

    if (dup == NULL || str == NULL)
        return NULL;
    while (i < len) {
        dup[i] = str[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char *remove_leading_zeros(char *str)
{
    int i = 0;
    int len = my_strlen(str);
    int start = 0;

    if (str == NULL || len == 0)
        return str;
    if (str[0] == '-')
        start = 1;
    i = start;
    while (str[i] == '0' && i < len - 1)
        i++;
    if (i > start) {
        while (str[i]) {
            str[start] = str[i];
            start++;
            i++;
        }
        str[start] = '\0';
    }
    return str;
}