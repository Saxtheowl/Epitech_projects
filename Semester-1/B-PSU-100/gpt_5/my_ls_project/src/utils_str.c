/*
** EPITECH PROJECT, 2025
** MY_LS
** File description:
** Epitech-style source file for my_ls project
*/
#include "my_ls.h"
#include <stdlib.h>

size_t my_strlen(const char *s)
{
    size_t n = 0;

    if (!s)
        return 0;
    while (s[n] != '\0')
        n++;
    return n;
}

char *my_strdup(const char *s)
{
    size_t n = my_strlen(s);
    char *p = (char *)malloc(n + 1);

    if (!p)
        return NULL;
    for (size_t i = 0; i < n; i++)
        p[i] = s[i];
    p[n] = '\0';
    return p;
}

int my_strcmp(const char *a, const char *b)
{
    size_t i = 0;

    while (a[i] && b[i] && a[i] == b[i])
        i++;
    return ((unsigned char)a[i]) - ((unsigned char)b[i]);
}
