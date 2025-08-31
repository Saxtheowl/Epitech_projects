/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** IO and parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fastatools.h"

int read_file(const char *path, char **out)
{
    FILE *f = fopen(path, "rb");
    long sz; char *buf;
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    sz = ftell(f); if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
    buf = malloc((size_t)sz + 1); if (!buf) { fclose(f); return 0; }
    if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return 0; }
    buf[sz] = '\0'; fclose(f); *out = buf; return 1;
}

int parse_fasta(const char *data, fasta_entry_t **entries, int *count)
{
    int cap = 8; int n = 0; const char *p = data; const char *line;
    fasta_entry_t *arr = malloc(sizeof(fasta_entry_t) * cap);
    if (!arr) return 0;
    while (*p) {
        while (*p == '\n') p++;
        if (*p == '\0') break;
        if (*p != '>') { free_fasta(arr, n); return 0; }
        line = p; while (*p && *p != '\n') p++;
        arr[n].header = strndup(line + 1, (size_t)(p - line - 1));
        arr[n].seq = calloc(1, 1);
        if (*p == '\n') p++;
        while (*p && *p != '>') {
            const char *s = p;
            while (*p && *p != '\n') p++;
            size_t old = strlen(arr[n].seq);
            arr[n].seq = realloc(arr[n].seq, old + (size_t)(p - s) + 1);
            memcpy(arr[n].seq + old, s, (size_t)(p - s));
            arr[n].seq[old + (size_t)(p - s)] = '\0';
            if (*p == '\n') p++;
        }
        if (++n >= cap) { cap *= 2; arr = realloc(arr, sizeof(fasta_entry_t) * cap); }
    }
    *entries = arr; *count = n; return 1;
}

void free_fasta(fasta_entry_t *entries, int count)
{
    int i;
    if (!entries) return;
    for (i = 0; i < count; ++i) { free(entries[i].header); free(entries[i].seq); }
    free(entries);
}

