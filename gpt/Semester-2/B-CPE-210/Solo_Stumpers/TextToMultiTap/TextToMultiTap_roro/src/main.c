/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "multitap.h"

static const char *key_for_char(char c, int *presses)
{
    char l;

    if (c == ' ') {
        *presses = 1;
        return "0";
    }
    if (!isalpha((unsigned char)c)) {
        *presses = 0;
        return "";
    }
    l = (char)tolower((unsigned char)c);
    if (l >= 'a' && l <= 'c') {
        *presses = (l - 'a') + 1;
        return "2";
    }
    if (l >= 'd' && l <= 'f') {
        *presses = (l - 'd') + 1;
        return "3";
    }
    if (l >= 'g' && l <= 'i') {
        *presses = (l - 'g') + 1;
        return "4";
    }
    if (l >= 'j' && l <= 'l') {
        *presses = (l - 'j') + 1;
        return "5";
    }
    if (l >= 'm' && l <= 'o') {
        *presses = (l - 'm') + 1;
        return "6";
    }
    if (l >= 'p' && l <= 's') {
        *presses = (l - 'p') + 1;
        return "7";
    }
    if (l >= 't' && l <= 'v') {
        *presses = (l - 't') + 1;
        return "8";
    }
    *presses = (l - 'w') + 1;
    return "9";
}

void text_to_multitap(const char *in, char *out, int max)
{
    int i;
    int k;
    int presses;
    const char *key;
    char last_key;

    k = 0;
    i = 0;
    last_key = '\0';
    while (in[i] != '\0' && k < max - 1) {
        key = key_for_char(in[i], &presses);
        if (presses > 0) {
            int p;

            if (last_key == key[0]) {
                if (k < max - 1) {
                    out[k] = ' ';
                    k = k + 1;
                }
            }
            p = 0;
            while (p < presses && k < max - 1) {
                out[k] = key[0];
                k = k + 1;
                p = p + 1;
            }
            last_key = key[0];
        } else if (key[0] == '0') {
            if (k < max - 1) {
                out[k] = '0';
                k = k + 1;
            }
            last_key = '\0';
        }
        i = i + 1;
    }
    out[k] = '\0';
}

int main(int argc, char **argv)
{
    char out[4096];

    if (argc != 2)
        return 84;
    text_to_multitap(argv[1], out, 4096);
    printf("%s\n", out);
    return 0;
}
