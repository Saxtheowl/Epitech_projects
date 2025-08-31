/*
** EPITECH PROJECT, 2024
** utils.c
** File description:
** Utility functions for string manipulation and conversions
*/

#include "../include/organized.h"
#include <stdlib.h>

int my_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char *my_strdup(const char *str)
{
    char *dup;
    int len;
    int i;

    if (!str)
        return NULL;
    
    len = my_strlen(str);
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    
    for (i = 0; i <= len; i++)
        dup[i] = str[i];
    return dup;
}

int my_strlen(const char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return 0;
    
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}