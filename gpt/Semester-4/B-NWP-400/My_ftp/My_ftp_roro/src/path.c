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
    char real_full[PATH_MAX];
    char real_dir[PATH_MAX];
    const char *last = NULL;
    size_t len = 0;

    if (inp[0] == '/')
        join_path(combined, sizeof(combined), home, inp + 1);
    else
        join_path(combined, sizeof(combined), cwd, inp);
    /* try full path first (works for existing files/dirs) */
    if (realpath(combined, real_full)) {
        if (strncmp(real_full, home, strlen(home)) != 0)
            return -1;
        my_strcpy(out, real_full, out_cap);
        return 0;
    }
    /* handle non-existent final component (e.g., STOR newfile) */
    len = my_strlen(combined);
    last = combined + len;
    while (last > combined && *(last - 1) != '/')
        last--;
    if (last == combined)
        return -1;
    /* temporarily terminate at directory slash */
    {
        char saved = *last;
        * (char *) last = '\0';
        if (!realpath(combined, real_dir)) {
            * (char *) last = saved;
            return -1;
        }
        * (char *) last = saved;
    }
    /* rebuild: real_dir + '/' + filename */
    join_path(real_full, sizeof(real_full), real_dir, last);
    if (strncmp(real_full, home, strlen(home)) != 0)
        return -1;
    my_strcpy(out, real_full, out_cap);
    return 0;
}
