#ifndef FASTATOOLS_H
#define FASTATOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct sequence {
    char *id;
    char *data;
    struct sequence *next;
} sequence_t;

typedef struct {
    char *str;
    int len;
    int capacity;
} string_builder_t;

// Main functions
void print_usage(void);
int process_option(int option, int k);

// FASTA parsing
sequence_t *parse_fasta(FILE *input);
void free_sequences(sequence_t *sequences);

// String utilities
string_builder_t *sb_create(void);
void sb_append(string_builder_t *sb, char c);
void sb_append_str(string_builder_t *sb, const char *str);
char *sb_to_string(string_builder_t *sb);
void sb_free(string_builder_t *sb);

// DNA processing
void clean_dna_sequence(char *seq);
char dna_complement(char c);
void reverse_string(char *str);
char *get_reverse_complement(const char *seq);
char *dna_to_rna(const char *seq);

// K-mers and coding sequences
char **get_kmers(sequence_t *sequences, int k, int *count);
char **get_coding_sequences(sequence_t *sequences, int *count);
char **get_amino_acids(sequence_t *sequences, int *count);

// Utilities
int compare_strings(const void *a, const void *b);
char codon_to_amino_acid(const char *codon);

#endif