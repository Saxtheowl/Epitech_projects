/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Character utility functions
*/

#include "text_to_multi_tap.h"

int is_valid_char(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ');
}

void write_char(char c)
{
    write(1, &c, 1);
}

char to_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}

char to_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

int is_upper(char c)
{
    return (c >= 'A' && c <= 'Z');
}