/*
** EPITECH PROJECT, 2024
** Day03 - Bootcamp Phoenix
** File description:
** my_putchar.c
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}