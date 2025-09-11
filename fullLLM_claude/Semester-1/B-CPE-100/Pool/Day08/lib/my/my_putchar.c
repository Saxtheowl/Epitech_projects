/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_putchar.c
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}