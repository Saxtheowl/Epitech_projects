/*
** EPITECH PROJECT, 2025
** My_ftp
** File description:
**   Path resolution within home
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include "ftp.h"

static void join_path(char *dst, size_t cap, const char *a, const char *b)
{
    size_t i = 0;
    my_strcpy(dst, a, cap);
    i = my_strlen(dst);
    if (i > 0 && i + 1 < cap && dst[i-1] != '/') dst[i++] = '/';
    for (size_t j = 0; b[j] && i + 1 < cap; ++j) dst[i++] = b[j];
    dst[i] = '\0';
}

int path_resolve(char *out, size_t out_cap, const char *home, const char *cwd,
    const char *inp)
{
    char combined[PATH_MAX];
    char real[PATH_MAX];

    if (inp[0] == '/')
        join_path(combined, sizeof(combined), home, inp + 1);
    else
        join_path(combined, sizeof(combined), cwd, inp);
    if (!realpath(combined, real))
        return -1;
    if (strncmp(real, home, strlen(home)) != 0)
        return -1;
    my_strcpy(out, real, out_cap);
    return 0;
}
