/*
** EPITECH PROJECT, 2025
** Lingo
** File description:
** Main and logic
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lingo.h"

void lingo_hint(const char *target, const char *guess, char *out, int max)
{
    int n;
    int i;
    int counts[256];

    n = (int)strlen(target);
    if ((int)strlen(guess) != n || max < n + 1) {
        if (max > 0)
            out[0] = '\0';
        return;
    }
    i = 0;
    while (i < 256) {
        counts[i] = 0;
        i = i + 1;
    }
    i = 0;
    while (i < n) {
        counts[(unsigned char)tolower((unsigned char)target[i])]++;
        i = i + 1;
    }
    i = 0;
    while (i < n) {
        if (tolower((unsigned char)guess[i]) ==
            tolower((unsigned char)target[i])) {
            out[i] = (char)toupper((unsigned char)guess[i]);
            counts[(unsigned char)tolower((unsigned char)guess[i])]--;
        } else {
            out[i] = '?';
        }
        i = i + 1;
    }
    i = 0;
    while (i < n) {
        if (out[i] == '?') {
            unsigned char g = (unsigned char)tolower((unsigned char)guess[i]);
            if (counts[g] > 0)
                out[i] = (char)tolower((unsigned char)guess[i]);
            else
                out[i] = '.';
            if (counts[g] > 0)
                counts[g]--;
        }
        i = i + 1;
    }
    out[n] = '\0';
}

int main(int argc, char **argv)
{
    char out[256];

    if (argc != 3)
        return 84;
    if (strlen(argv[1]) != strlen(argv[2]))
        return 84;
    lingo_hint(argv[1], argv[2], out, 256);
    if (out[0] == '\0')
        return 84;
    printf("%s\n", out);
    return 0;
}

