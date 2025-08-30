/*
** EPITECH PROJECT, 2024
** string_basic.c
** File description:
** basic string functions
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int length = 0;

    if (str == NULL)
        return 0;
    while (str[length] != '\0')
        length++;
    return length;
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return dest;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return dest;
    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

char *my_revstr(char *str)
{
    int len = 0;
    int i = 0;
    char temp = 0;

    if (str == NULL)
        return NULL;
    len = my_strlen(str);
    for (i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}