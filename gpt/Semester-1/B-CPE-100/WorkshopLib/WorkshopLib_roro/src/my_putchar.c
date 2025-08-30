/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** my_putchar
*/

#include <unistd.h>

int my_putchar(char c)
{
    return (int)write(1, &c, 1);
}
