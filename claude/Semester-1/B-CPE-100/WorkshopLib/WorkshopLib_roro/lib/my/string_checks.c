/*
** EPITECH PROJECT, 2024
** string_checks.c
** File description:
** string checking functions
*/

#include "../../include/my.h"

int my_str_isalpha(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z')))
            return 0;
        i++;
    }
    return 1;
}

int my_str_isnum(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        i++;
    }
    return 1;
}

int my_str_islower(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!(str[i] >= 'a' && str[i] <= 'z'))
            return 0;
        i++;
    }
    return 1;
}

int my_str_isupper(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!(str[i] >= 'A' && str[i] <= 'Z'))
            return 0;
        i++;
    }
    return 1;
}

int my_str_isprintable(char const *str)
{
    int i = 0;

    if (str == NULL || str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!(str[i] >= 32 && str[i] <= 126))
            return 0;
        i++;
    }
    return 1;
}