/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** writes a string to standard output
*/

#include "../include/my.h"

int my_putstr(char const *str)
{
    int count = 0;

    if (str == NULL) {
        my_putstr("(null)");
        return 6;
    }
    while (str[count]) {
        my_putchar(str[count]);
        count++;
    }
    return count;
}