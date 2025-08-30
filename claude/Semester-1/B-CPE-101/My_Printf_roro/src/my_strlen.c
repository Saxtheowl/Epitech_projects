/*
** EPITECH PROJECT, 2024
** my_strlen.c
** File description:
** returns the length of a string
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int len = 0;

    if (str == NULL)
        return 0;
    while (str[len])
        len++;
    return len;
}