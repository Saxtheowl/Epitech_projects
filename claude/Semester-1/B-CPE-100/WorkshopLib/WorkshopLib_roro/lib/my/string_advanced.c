/*
** EPITECH PROJECT, 2024
** string_advanced.c
** File description:
** advanced string functions
*/

#include "../../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL)
        return 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (s1 == NULL || s2 == NULL || n <= 0)
        return 0;
    while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}

char *my_strcat(char *dest, char const *src)
{
    int dest_len = 0;
    int i = 0;

    if (dest == NULL || src == NULL)
        return dest;
    dest_len = my_strlen(dest);
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *my_strncat(char *dest, char const *src, int nb)
{
    int dest_len = 0;
    int i = 0;

    if (dest == NULL || src == NULL)
        return dest;
    dest_len = my_strlen(dest);
    while (i < nb && src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
    return dest;
}