/*
** EPITECH PROJECT, 2025
** Rush1
** File description:
** my_putchar function for testing
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}