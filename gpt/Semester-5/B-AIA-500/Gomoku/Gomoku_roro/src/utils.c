/*
** EPITECH PROJECT, 2025
** Gomoku_roro
** File description:
**   Utilities
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *str_trim(char *s)
{
    char *e;

    while (*s && isspace((unsigned char)*s))
        s++;
    e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1]))
        *--e = '\0';
    return s;
}

int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    v = strtol(s, &end, 10);
    if (s == end)
        return 1;
    *out = (int)v;
    return 0;
}

int split_at(const char *s, char sep, char *left, size_t lsz,
    char *right, size_t rsz)
{
    const char *p;
    size_t ln, rn;

    p = strchr(s, sep);
    if (!p)
        return 1;
    ln = (size_t)(p - s);
    rn = strlen(p + 1);
    if (ln + 1 > lsz || rn + 1 > rsz)
        return 1;
    memcpy(left, s, ln);
    left[ln] = '\0';
    memcpy(right, p + 1, rn + 1);
    return 0;
}

