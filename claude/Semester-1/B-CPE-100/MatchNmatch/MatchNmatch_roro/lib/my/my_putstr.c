/*
** EPITECH PROJECT, 2024
** my_putstr
** File description:
** writes a string to standard output
*/

#include <stddef.h>
#include "../../include/my.h"

int my_putstr(char const *str)
{
    int length = 0;

    if (str == NULL)
        return -1;
    while (str[length] != '\0') {
        my_putchar(str[length]);
        length++;
    }
    return length;
}