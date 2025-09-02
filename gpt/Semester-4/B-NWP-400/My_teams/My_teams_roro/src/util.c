/*
** EPITECH PROJECT, 2025
** My_teams_roro
** File description:
**   Utils
*/

#include <stdlib.h>
#include "myteams.h"

int parse_int(const char *s, int *out)
{
    char *end = NULL;
    long v = strtol(s, &end, 10);
    if (!s || s == end || *end != '\0' || v <= 0 || v > 65535)
        return -1;
    *out = (int)v;
    return 0;
}

size_t my_strlen(const char *s)
{
    size_t i = 0; while (s && s[i]) i++; return i;
}

void my_strcpy(char *dst, const char *src, size_t cap)
{
    size_t i = 0; if (cap == 0) return; if (!src) { dst[0] = '\0'; return; }
    while (src[i] && i + 1 < cap) { dst[i] = src[i]; i++; }
    dst[i] = '\0';
}

