/*
** EPITECH PROJECT, 2025
** Antman_roro
** File description:
** Common file helpers
*/

#include <stdio.h>
#include <stdlib.h>
#include "antman.h"

static char *read_file(const char *path, size_t *out_n)
{
    FILE *fp;
    char *buf;
    size_t n;

    fp = fopen(path, "rb");
    if (!fp)
        return NULL;
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return NULL; }
    n = (size_t)ftell(fp);
    rewind(fp);
    buf = malloc(n + 1);
    if (!buf) { fclose(fp); return NULL; }
    if (fread(buf, 1, n, fp) != n) { free(buf); fclose(fp); return NULL; }
    buf[n] = '\0';
    fclose(fp);
    if (out_n)
        *out_n = n;
    return buf;
}

int antman(const char *path)
{
    size_t n;
    char *s;
    size_t i;

    s = read_file(path, &n);
    if (!s)
        return ERR_CODE;
    i = 0;
    while (i < n) {
        unsigned char ch = (unsigned char)s[i];
        size_t j = i + 1;
        size_t run = 1;
        while (j < n && s[j] == (char)ch && run < 255) { j += 1; run += 1; }
        fputc((int)run, stdout);
        fputc((int)ch, stdout);
        i = j;
    }
    free(s);
    return 0;
}

int giantman(const char *path)
{
    size_t n;
    char *s;
    size_t i;

    s = read_file(path, &n);
    if (!s)
        return ERR_CODE;
    i = 0;
    while (i + 1 < n) {
        unsigned char count = (unsigned char)s[i++];
        unsigned char ch = (unsigned char)s[i++];
        while (count--) fputc(ch, stdout);
    }
    free(s);
    return 0;
}
