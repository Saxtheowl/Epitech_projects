/*
** EPITECH PROJECT, 2025
** Mixword
** File description:
** Main and logic
*/

#include <stdio.h>
#include "mixword.h"

void mixword(const char *a, const char *b, char *out, int max)
{
    int i;
    int j;
    int k;
    int turn;

    i = 0;
    j = 0;
    k = 0;
    turn = 0;
    while ((a[i] != '\0' || b[j] != '\0') && k < max - 1) {
        if ((turn == 0 && a[i] != '\0') || b[j] == '\0') {
            out[k] = a[i];
            i = i + 1;
            k = k + 1;
        } else if (b[j] != '\0') {
            out[k] = b[j];
            j = j + 1;
            k = k + 1;
        }
        turn = 1 - turn;
    }
    out[k] = '\0';
}

int main(int argc, char **argv)
{
    char out[4096];

    if (argc != 3)
        return 84;
    mixword(argv[1], argv[2], out, 4096);
    printf("%s\n", out);
    return 0;
}

