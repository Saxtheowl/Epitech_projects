/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Utilities
*/

#include <ctype.h>
#include <unistd.h>
#include "ftp.h"

int str_ieq(const char *a, const char *b)
{
    size_t i = 0;
    while (a[i] && b[i]) {
        if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i]))
            return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int starts_with(const char *s, const char *p)
{
    size_t i = 0;
    while (p[i]) {
        if (s[i] != p[i])
            return 0;
        i++;
    }
    return 1;
}

size_t my_strlen(const char *s)
{
    size_t i = 0;
    while (s[i]) i++;
    return i;
}

void my_strcpy(char *dst, const char *src, size_t cap)
{
    size_t i = 0;
    if (cap == 0) return;
    while (src[i] && i + 1 < cap) {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

