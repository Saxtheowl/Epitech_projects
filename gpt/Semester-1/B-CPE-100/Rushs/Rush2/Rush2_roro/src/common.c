/*
** EPITECH PROJECT, 2025
** Rush2_roro
** File description:
** Common helpers
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "rush2.h"

static int read_all(char *buf, size_t cap, size_t *out)
{
    size_t n = 0;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (n + 1 >= cap)
            break;
        buf[n++] = (char)ch;
    }
    buf[n] = '\0';
    if (out) *out = n;
    return 0;
}

int step01_main(void)
{
    char buf[65536];
    size_t n;
    int freq[26];
    int i;

    for (i = 0; i < 26; ++i) freq[i] = 0;
    read_all(buf, sizeof(buf), &n);
    for (i = 0; (size_t)i < n; ++i) {
        unsigned char c = (unsigned char)buf[i];
        if (isalpha(c)) {
            int idx = tolower(c) - 'a';
            if (idx >= 0 && idx < 26) freq[idx] += 1;
        }
    }
    /* output letters sorted by frequency desc, alphabet asc */
    {
        int idxs[26];
        int j;
        for (i = 0; i < 26; ++i) idxs[i] = i;
        for (i = 0; i < 26; ++i) {
            for (j = i + 1; j < 26; ++j) {
                int ai = idxs[i];
                int aj = idxs[j];
                if (freq[aj] > freq[ai] || (freq[aj] == freq[ai] && aj < ai)) {
                    int t = idxs[i]; idxs[i] = idxs[j]; idxs[j] = t;
                }
            }
        }
        for (i = 0; i < 26; ++i) {
            if (freq[idxs[i]] == 0)
                continue;
            putchar('a' + idxs[i]);
        }
        putchar('\n');
    }
    return 0;
}

static int is_valid_alpha(const char *a)
{
    int seen[256];
    int i;

    if (!a) return 0;
    for (i = 0; i < 256; ++i) seen[i] = 0;
    for (i = 0; a[i]; ++i) {
        unsigned char c = (unsigned char)a[i];
        if (!isalpha(c)) return 0;
        if (seen[c]) return 0;
        seen[c] = 1;
    }
    if (i != 26)
        return 0;
    return 1;
}

int step02_main(const char *alphabet)
{
    return is_valid_alpha(alphabet) ? 0 : ERR_CODE;
}

static void build_maps(const char *alphabet, int enc[256], int dec[256])
{
    int i;

    for (i = 0; i < 256; ++i) enc[i] = dec[i] = -1;
    for (i = 0; i < 26; ++i) {
        unsigned char p = (unsigned char)('a' + i);
        unsigned char c = (unsigned char)tolower((unsigned char)alphabet[i]);
        enc[p] = c;
        enc[toupper(p)] = toupper(c);
        dec[c] = p;
        dec[toupper(c)] = toupper(p);
    }
}

int step03_main(const char *alphabet)
{
    char buf[65536];
    size_t n;
    int enc[256], dec[256];
    int i;

    if (!is_valid_alpha(alphabet))
        return ERR_CODE;
    build_maps(alphabet, enc, dec);
    read_all(buf, sizeof(buf), &n);
    for (i = 0; (size_t)i < n; ++i) {
        unsigned char c = (unsigned char)buf[i];
        if (enc[c] != -1)
            buf[i] = (char)enc[c];
    }
    fwrite(buf, 1, n, stdout);
    return 0;
}

int step04_main(const char *alphabet)
{
    char buf[65536];
    size_t n;
    int enc[256], dec[256];
    int i;

    if (!is_valid_alpha(alphabet))
        return ERR_CODE;
    build_maps(alphabet, enc, dec);
    read_all(buf, sizeof(buf), &n);
    for (i = 0; (size_t)i < n; ++i) {
        unsigned char c = (unsigned char)buf[i];
        if (dec[c] != -1)
            buf[i] = (char)dec[c];
    }
    fwrite(buf, 1, n, stdout);
    return 0;
}
