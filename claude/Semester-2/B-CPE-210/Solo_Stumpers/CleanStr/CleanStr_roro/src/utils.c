/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Utility functions for clean_str
*/

#include "clean_str.h"

int is_separator(char c)
{
    return (c == ' ' || c == '\t');
}

void my_putchar(char c)
{
    write(1, &c, 1);
}