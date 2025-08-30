/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** my_putstr
*/

#include <unistd.h>
#include <stddef.h>

size_t my_strlen(const char *s);

int my_putstr(const char *s)
{
    size_t n;

    if (s == NULL)
        return -1;
    for (n = 0; s[n] != '\0'; ++n)
        ;
    return (int)write(1, s, n);
}
