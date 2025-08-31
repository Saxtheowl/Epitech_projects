/*
** EPITECH PROJECT, 2025
** GeekNameFormatter
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include "geek_name.h"

static char map_char(char c)
{
    char l;

    l = (char)tolower((unsigned char)c);
    if (l == 'a')
        return '4';
    if (l == 'e')
        return '3';
    if (l == 'i')
        return '1';
    if (l == 'o')
        return '0';
    if (l == 's')
        return '5';
    if (l == 't')
        return '7';
    return c;
}

void geekify(const char *in, char *out, int max)
{
    int i;
    int k;

    i = 0;
    k = 0;
    while (in[i] != '\0' && k < max - 1) {
        out[k] = map_char(in[i]);
        k = k + 1;
        i = i + 1;
    }
    out[k] = '\0';
}

int main(int argc, char **argv)
{
    char out[4096];

    if (argc != 2)
        return 84;
    geekify(argv[1], out, 4096);
    printf("%s\n", out);
    return 0;
}

