/*
** EPITECH PROJECT, 2025
** USNameFormatter
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "us_name.h"

static void trim_and_split(const char *s, char parts[][64], int *count)
{
    int i;
    int j;

    *count = 0;
    i = 0;
    j = 0;
    while (s[i] != '\0' && *count < 16) {
        if (!isspace((unsigned char)s[i])) {
            parts[*count][j] = s[i];
            j = j + 1;
            if (j >= 63) {
                parts[*count][j] = '\0';
                *count = *count + 1;
                j = 0;
            }
        } else if (j > 0) {
            parts[*count][j] = '\0';
            *count = *count + 1;
            j = 0;
        }
        i = i + 1;
    }
    if (j > 0 && *count < 16) {
        parts[*count][j] = '\0';
        *count = *count + 1;
    }
}

static void to_lower(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0') {
        s[i] = (char)tolower((unsigned char)s[i]);
        i = i + 1;
    }
}

static void capitalize(char *s)
{
    if (s[0] != '\0')
        s[0] = (char)toupper((unsigned char)s[0]);
}

static void upper_str(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0') {
        s[i] = (char)toupper((unsigned char)s[i]);
        i = i + 1;
    }
}

void format_name_us(const char *in, char *out, int max)
{
    char parts[16][64];
    int count;
    int i;
    int k;

    trim_and_split(in, parts, &count);
    if (count == 0) {
        out[0] = '\0';
        return;
    }
    i = 0;
    while (i < count) {
        to_lower(parts[i]);
        capitalize(parts[i]);
        i = i + 1;
    }
    to_lower(parts[count - 1]);
    upper_str(parts[count - 1]);
    k = snprintf(out, max, "%s", parts[count - 1]);
    if (count > 1 && k < max - 1)
        k += snprintf(out + k, max - k, ", ");
    i = 0;
    while (i < count - 1 && k < max - 1) {
        k += snprintf(out + k, max - k, "%s", parts[i]);
        if (i + 1 < count - 1 && k < max - 1)
            k += snprintf(out + k, max - k, " ");
        i = i + 1;
    }
}

int main(int argc, char **argv)
{
    char out[256];

    if (argc != 2)
        return 84;
    format_name_us(argv[1], out, 256);
    if (out[0] == '\0')
        return 84;
    printf("%s\n", out);
    return 0;
}

