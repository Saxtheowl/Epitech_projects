/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** Main and logic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fractals.h"

static void fill(char *buf, int w, int h, char ch)
{
    int i;

    i = 0;
    while (i < w * h) {
        buf[i] = ch;
        i = i + 1;
    }
}

static void draw_carpet(char *buf, int x, int y, int size, int w)
{
    int i;
    int j;
    int n;

    if (size == 1)
        return;
    n = size / 3;
    i = 0;
    while (i < n) {
        j = 0;
        while (j < n) {
            buf[(y + n + i) * w + (x + n + j)] = ' ';
            j = j + 1;
        }
        i = i + 1;
    }
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 3) {
            if (!(i == 1 && j == 1))
                draw_carpet(buf, x + j * n, y + i * n, n, w);
            j = j + 1;
        }
        i = i + 1;
    }
}

void sierpinski(int n, char *out, int max)
{
    int size;
    char *buf;
    int i;
    int k;

    size = 1;
    i = 0;
    while (i < n) {
        size = size * 3;
        i = i + 1;
    }
    if (max < size * (size + 1)) {
        if (max > 0)
            out[0] = '\0';
        return;
    }
    buf = malloc((size_t)(size * size));
    if (!buf) {
        if (max > 0)
            out[0] = '\0';
        return;
    }
    fill(buf, size, size, '#');
    draw_carpet(buf, 0, 0, size, size);
    k = 0;
    i = 0;
    while (i < size) {
        int j = 0;
        while (j < size) {
            out[k] = buf[i * size + j];
            k = k + 1;
            j = j + 1;
        }
        out[k] = '\n';
        k = k + 1;
        i = i + 1;
    }
    out[k - 1] = '\0';
    free(buf);
}

int main(int argc, char **argv)
{
    int n;
    char *end;
    long v;
    char *out;

    if (argc != 2)
        return 84;
    v = strtol(argv[1], &end, 10);
    if (*end != '\0' || v < 0 || v > 5)
        return 84;
    n = (int)v;
    out = malloc(1000000);
    if (!out)
        return 84;
    sierpinski(n, out, 1000000);
    if (out[0] == '\0') {
        free(out);
        return 84;
    }
    printf("%s\n", out);
    free(out);
    return 0;
}

