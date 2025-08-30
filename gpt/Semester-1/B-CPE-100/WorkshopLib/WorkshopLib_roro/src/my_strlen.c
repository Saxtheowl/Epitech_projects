/*
** EPITECH PROJECT, 2025
** WorkshopLib_roro
** File description:
** my_strlen
*/

#include <stddef.h>

size_t my_strlen(const char *s)
{
    const char *p;

    if (s == NULL)
        return 0;
    p = s;
    while (*p)
        ++p;
    return (size_t)(p - s);
}
