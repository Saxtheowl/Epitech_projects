/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Prototypes
*/

#ifndef FASTATOOLS_H
    #define FASTATOOLS_H

typedef struct {
    char *header;
    char *seq;
} fasta_entry_t;

int read_file(const char *path, char **out);
int parse_fasta(const char *data, fasta_entry_t **entries, int *count);
void free_fasta(fasta_entry_t *entries, int count);
char *revcomp(const char *seq);
void print_stats(fasta_entry_t *entries, int count);

#endif /* FASTATOOLS_H */

