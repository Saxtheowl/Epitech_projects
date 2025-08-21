/*
** EPITECH PROJECT, 2024
** libmy
** File description:
** puts a char on the standard output
*/

#include "../../include/my.h"

int my_putchar(char c)
{
    return write(1, &c, 1);
}