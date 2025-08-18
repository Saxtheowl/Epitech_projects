/*
** EPITECH PROJECT, 2025
** my_ls
** File description:
** Helpers to join paths safely.
*/
#include "my_ls.h"
#include <unistd.h>

int join_path(char *out, size_t outsz, const char *a, const char *b)
{
    size_t i = 0;
    size_t j = 0;

    if (!out || outsz == 0) return -1;
    if (!a) a = "";
    if (!b) b = "";
    while (a[i] && i + 1 < outsz) { out[i] = a[i]; ++i; }
    if (i > 0 && out[i - 1] != '/' && i + 1 < outsz) out[i++] = '/';
    while (b[j] && i + 1 < outsz) { out[i++] = b[j++]; }
    if (i >= outsz) return -1;
    out[i] = '\0';
    return 0;
}
