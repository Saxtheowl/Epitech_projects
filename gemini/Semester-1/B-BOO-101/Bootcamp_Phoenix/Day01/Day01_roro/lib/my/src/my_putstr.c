/*
** EPITECH PROJECT, 2025
** Day01_roro
** File description:
** my_putstr
*/

#include <unistd.h>

#include "my.h"

void my_putstr(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
}
