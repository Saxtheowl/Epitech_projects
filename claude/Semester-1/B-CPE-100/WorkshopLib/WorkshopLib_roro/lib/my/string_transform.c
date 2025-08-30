/*
** EPITECH PROJECT, 2024
** string_transform.c
** File description:
** string transformation functions
*/

#include "../../include/my.h"

char *my_strupcase(char *str)
{
    int i = 0;

    if (str == NULL)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;
        i++;
    }
    return str;
}

char *my_strlowcase(char *str)
{
    int i = 0;

    if (str == NULL)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
        i++;
    }
    return str;
}

char *my_strcapitalize(char *str)
{
    int i = 0;
    int capitalize_next = 1;

    if (str == NULL)
        return NULL;
    while (str[i] != '\0') {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= '0' && str[i] <= '9')) {
            if (capitalize_next && str[i] >= 'a' && str[i] <= 'z')
                str[i] = str[i] - 32;
            else if (!capitalize_next && str[i] >= 'A' && str[i] <= 'Z')
                str[i] = str[i] + 32;
            capitalize_next = 0;
        } else {
            capitalize_next = 1;
        }
        i++;
    }
    return str;
}