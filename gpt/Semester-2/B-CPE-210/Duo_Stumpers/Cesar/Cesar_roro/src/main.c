/*
** EPITECH PROJECT, 2025
** Cesar
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "cesar.h"

int parse_int(const char *s, int *out)
{
    char *end;
    long v;

    if (s == NULL || *s == '\0' || out == NULL)
        return 0;
    v = strtol(s, &end, 10);
    if (*end != '\0')
        return 0;
    *out = (int)v;
    return 1;
}

void cesar_cipher(const char *in, char *out, int max, int shift)
{
    int i;
    int k;

    k = 0;
    i = 0;
    while (in[i] != '\0' && k < max - 1) {
        if (isalpha((unsigned char)in[i])) {
            int base;
            int offset;

            base = isupper((unsigned char)in[i]) ? 'A' : 'a';
            offset = (in[i] - base + (shift % 26) + 26) % 26;
            out[k] = (char)(base + offset);
            k = k + 1;
        } else {
            out[k] = in[i];
            k = k + 1;
        }
        i = i + 1;
    }
    out[k] = '\0';
}

int main(int argc, char **argv)
{
    int shift;
    char out[4096];

    if (argc != 3 || !parse_int(argv[1], &shift))
        return 84;
    cesar_cipher(argv[2], out, 4096, shift);
    printf("%s\n", out);
    return 0;
}

