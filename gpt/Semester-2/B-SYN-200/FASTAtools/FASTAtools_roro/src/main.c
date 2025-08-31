/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** CLI
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fastatools.h"

static void usage(void)
{
    puts("Usage: fastatools (-r|-s) <file.fasta>");
}

int main(int argc, char **argv)
{
    char *data; fasta_entry_t *entries; int count;
    if (argc != 3) { usage(); return 84; }
    if (!read_file(argv[2], &data)) return 84;
    if (!parse_fasta(data, &entries, &count)) { free(data); return 84; }
    if (strcmp(argv[1], "-r") == 0) {
        int i;
        for (i = 0; i < count; ++i) {
            char *rc = revcomp(entries[i].seq);
            if (!rc) { free_fasta(entries, count); free(data); return 84; }
            printf(">%s\n%s\n", entries[i].header, rc);
            free(rc);
        }
    } else if (strcmp(argv[1], "-s") == 0) {
        print_stats(entries, count);
    } else {
        usage(); free_fasta(entries, count); free(data); return 84;
    }
    free_fasta(entries, count); free(data); return 0;
}

