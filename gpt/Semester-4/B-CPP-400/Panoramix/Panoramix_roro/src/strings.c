/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
**   Small string helpers
*/

#include <unistd.h>
#include <limits.h>
#include "panoramix.h"

int my_strcmp(const char *a, const char *b)
{
    int i = 0;

    if (!a && !b)
        return 0;
    if (!a)
        return -1;
    if (!b)
        return 1;
    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return ((unsigned char)a[i] - (unsigned char)b[i]);
}

int my_atoi_strict(const char *s, int *out)
{
    long v = 0;
    int i = 0;

    if (!s || !*s)
        return -1;
    while (s[i]) {
        if (s[i] < '0' || s[i] > '9')
            return -1;
        v = v * 10 + (s[i] - '0');
        if (v > INT_MAX)
            return -1;
        i++;
    }
    *out = (int)v;
    return 0;
}

int my_dprintf(int fd, const char *s)
{
    int len = 0;

    while (s[len])
        len++;
    return (int)write(fd, s, (unsigned)len);
}

