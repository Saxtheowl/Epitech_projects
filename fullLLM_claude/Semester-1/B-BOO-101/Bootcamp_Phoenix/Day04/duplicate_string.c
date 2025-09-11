/*
** EPITECH PROJECT, 2024
** Day04 - Bootcamp Phoenix
** File description:
** duplicate_string.c
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
    int len = 0;

    while (str[len] != '\0')
        len++;
    return len;
}

char *duplicate_string(char const *src)
{
    int len;
    char *duplicate;
    int i = 0;

    if (src == NULL)
        return NULL;

    len = my_strlen(src);
    duplicate = malloc(sizeof(char) * (len + 1));
    
    if (duplicate == NULL)
        return NULL;

    while (src[i] != '\0') {
        duplicate[i] = src[i];
        i++;
    }
    duplicate[i] = '\0';

    return duplicate;
}