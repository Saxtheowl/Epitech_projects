/*
** EPITECH PROJECT, 2024
** libmy
** File description:
** my_strlen function
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return 0;
    while (str[len] != '\0')
        len++;
    return len;
}