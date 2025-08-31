/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Operations: reverse complement and stats
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "fastatools.h"

static char comp_base(char c)
{
    char u = (char)toupper((unsigned char)c);
    if (u == 'A') return 'T';
    if (u == 'T' || u == 'U') return 'A';
    if (u == 'C') return 'G';
    if (u == 'G') return 'C';
    return 'N';
}

char *revcomp(const char *seq)
{
    size_t n = strlen(seq);
    char *rc = malloc(n + 1);
    size_t i = 0;
    if (!rc) return NULL;
    while (i < n) {
        rc[i] = comp_base(seq[n - 1 - i]);
        i++;
    }
    rc[n] = '\0';
    return rc;
}

void print_stats(fasta_entry_t *entries, int count)
{
    int i;
    size_t total = 0;
    for (i = 0; i < count; ++i) total += strlen(entries[i].seq);
    printf("sequences: %d\n", count);
    printf("total_bases: %zu\n", total);
}

