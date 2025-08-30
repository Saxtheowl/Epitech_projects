/*
** EPITECH PROJECT, 2024
** my_putchar.c
** File description:
** writes a character to standard output
*/

#include <unistd.h>

int my_putchar(char c)
{
    write(1, &c, 1);
    return 1;
}