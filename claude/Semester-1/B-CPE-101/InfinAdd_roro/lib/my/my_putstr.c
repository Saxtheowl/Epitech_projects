/*
** EPITECH PROJECT, 2024
** my_putstr.c
** File description:
** writes a string to standard output
*/

#include "../../include/infin_add.h"

void my_putstr(char const *str)
{
    if (str == NULL)
        return;
    while (*str) {
        my_putchar(*str);
        str++;
    }
}