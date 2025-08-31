/*
** EPITECH PROJECT, 2025
** Game_of_Stones_roro
** File description:
** utils
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "gos.h"

char *str_dup(const char *s)
{
    size_t n;
    char *p;

    if (!s)
        return NULL;
    n = strlen(s);
    p = (char *)xcalloc(n + 1, 1);
    memcpy(p, s, n);
    return p;
}

char *str_trim(char *s)
{
    size_t i;
    size_t j;

    if (!s)
        return s;
    i = 0;
    while (s[i] && isspace((unsigned char)s[i]))
        i += 1;
    j = strlen(s);
    while (j > i && isspace((unsigned char)s[j - 1]))
        j -= 1;
    memmove(s, s + i, j - i);
    s[j - i] = '\0';
    return s;
}

bool starts_with(const char *s, const char *prefix)
{
    size_t i;

    for (i = 0; prefix[i]; ++i)
        if (s[i] != prefix[i])
            return false;
    return true;
}

void *xcalloc(size_t nmemb, size_t size)
{
    void *p;

    p = calloc(nmemb, size);
    if (!p) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(84);
    }
    return p;
}

void *xrealloc(void *ptr, size_t size)
{
    void *p;

    p = realloc(ptr, size);
    if (!p) {
        fprintf(stderr, "Memory allocation failure\n");
        exit(84);
    }
    return p;
}

