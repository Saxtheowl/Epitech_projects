/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Header file for FASTAtools project
*/

#ifndef FASTATOOLS_H_
#define FASTATOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

typedef struct sequence_s {
    char *id;
    char *data;
    struct sequence_s *next;
} sequence_t;

typedef struct kmer_s {
    char *kmer;
    struct kmer_s *next;
} kmer_t;

// Required function
char *my_strcapitalize_synthesis(char *str);

// Main functions
int parse_arguments(int ac, char **av, int *option, int *k);
void print_usage(int k_option);
sequence_t *read_fasta(void);
void free_sequences(sequence_t *sequences);
void free_kmers(kmer_t *kmers);

// Processing functions
void process_dna(sequence_t *sequences);
void process_rna(sequence_t *sequences);
void process_reverse_complement(sequence_t *sequences);
void process_kmers(sequence_t *sequences, int k);
void process_coding_sequences(sequence_t *sequences);
void process_amino_acids(sequence_t *sequences);
void process_alignment(sequence_t *sequences);

// Utility functions
char *clean_dna_sequence(char *sequence);
char *dna_to_rna(char *dna);
char *reverse_complement(char *dna);
kmer_t *extract_kmers(sequence_t *sequences, int k);
void sort_kmers(kmer_t **kmers);
void add_kmer(kmer_t **kmers, char *kmer_str);
sequence_t *find_coding_sequences(sequence_t *sequences);
char *translate_to_amino_acid(char *codon);
int my_strlen(char *str);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char *src);
char *my_strcpy(char *dest, char *src);
char *my_strncpy(char *dest, char *src, int n);
int is_valid_dna_char(char c);
int is_start_codon(char *codon);
int is_stop_codon(char *codon);

#endif /* !FASTATOOLS_H_ */