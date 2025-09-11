/*
** EPITECH PROJECT, 2024
** Day06 - B-CPE-100
** File description:
** my_putchar.c - For testing purposes only
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}