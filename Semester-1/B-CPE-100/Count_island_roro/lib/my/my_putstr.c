/*
** EPITECH PROJECT, 2024
** libmy
** File description:
** puts a string on the standard output
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    if (!str)
        return -1;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return 0;
}