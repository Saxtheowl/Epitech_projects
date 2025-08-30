/*
** EPITECH PROJECT, 2024
** my_strlen
** File description:
** returns length of string
*/

#include <stddef.h>

int my_strlen(char const *str)
{
    int length = 0;

    if (str == NULL)
        return 0;
    while (str[length] != '\0')
        length++;
    return length;
}