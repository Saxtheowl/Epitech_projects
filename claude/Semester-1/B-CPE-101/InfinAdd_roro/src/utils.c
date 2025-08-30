/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** utility functions for infinite addition
*/

#include <stdlib.h>
#include "../include/infin_add.h"

int my_strlen(char const *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len])
        len++;
    return len;
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