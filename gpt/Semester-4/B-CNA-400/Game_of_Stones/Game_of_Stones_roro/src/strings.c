/*
** EPITECH PROJECT, 2025
** Game_of_Stones
** File description:
**   String helpers
*/

#include <stdlib.h>
#include <ctype.h>
#include "gos.h"

int gos_strcmp(const char *a, const char *b)
{
    size_t i = 0;

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

size_t gos_strlen(const char *s)
{
    size_t i = 0;

    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

char *gos_strdup(const char *s)
{
    size_t len = gos_strlen(s);
    char *dup = NULL;
    size_t i = 0;

    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    for (i = 0; i < len; ++i)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

char *gos_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *dup = NULL;
    size_t i = 0;

    if (!s)
        return NULL;
    while (s[len] && len < n)
        len++;
    dup = malloc(len + 1);
    if (!dup)
        return NULL;
    for (i = 0; i < len; ++i)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

void gos_free_array(char **arr, size_t n)
{
    size_t i = 0;

    if (!arr)
        return;
    for (i = 0; i < n; ++i) {
        free(arr[i]);
    }
    free(arr);
}

char *gos_trim(char *s)
{
    size_t i = 0;
    size_t j = 0;
    size_t len = 0;

    if (!s)
        return NULL;
    len = gos_strlen(s);
    i = 0;
    while (i < len && isspace((unsigned char)s[i]))
        i++;
    j = len;
    while (j > i && isspace((unsigned char)s[j - 1]))
        j--;
    s[j] = '\0';
    return s + i;
}

