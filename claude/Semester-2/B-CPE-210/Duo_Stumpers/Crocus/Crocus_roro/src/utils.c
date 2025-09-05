/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** utils
*/

#include "crocus.h"

int my_strlen(char *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len])
        len++;
    return len;
}

int is_valid_number(char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}