/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Processing functions for different FASTA operations
*/

#include "fastatools.h"

void process_dna(sequence_t *sequences)
{
    sequence_t *current = sequences;
    
    while (current) {
        printf(">%s\n", current->id);
        printf("%s\n", current->data);
        current = current->next;
    }
}

char *dna_to_rna(char *dna)
{
    char *rna;
    int i;
    int len;
    
    if (!dna)
        return NULL;
    
    len = my_strlen(dna);
    rna = malloc(len + 1);
    if (!rna)
        return NULL;
    
    for (i = 0; i < len; i++) {
        if (dna[i] == 'T')
            rna[i] = 'U';
        else
            rna[i] = dna[i];
    }
    rna[i] = '\0';
    
    return rna;
}

void process_rna(sequence_t *sequences)
{
    sequence_t *current = sequences;
    
    while (current) {
        char *rna = dna_to_rna(current->data);
        printf(">%s\n", current->id);
        if (rna) {
            printf("%s\n", rna);
            free(rna);
        }
        current = current->next;
    }
}

char *reverse_complement(char *dna)
{
    char *rev_comp;
    int len;
    int i;
    
    if (!dna)
        return NULL;
    
    len = my_strlen(dna);
    rev_comp = malloc(len + 1);
    if (!rev_comp)
        return NULL;
    
    for (i = 0; i < len; i++) {
        switch (dna[len - 1 - i]) {
        case 'A':
            rev_comp[i] = 'T';
            break;
        case 'T':
            rev_comp[i] = 'A';
            break;
        case 'G':
            rev_comp[i] = 'C';
            break;
        case 'C':
            rev_comp[i] = 'G';
            break;
        case 'N':
            rev_comp[i] = 'N';
            break;
        default:
            rev_comp[i] = dna[len - 1 - i];
            break;
        }
    }
    rev_comp[len] = '\0';
    
    return rev_comp;
}

void process_reverse_complement(sequence_t *sequences)
{
    sequence_t *current = sequences;
    
    while (current) {
        char *rev_comp = reverse_complement(current->data);
        printf(">%s\n", current->id);
        if (rev_comp) {
            printf("%s\n", rev_comp);
            free(rev_comp);
        }
        current = current->next;
    }
}

int is_start_codon(char *codon)
{
    return (codon && my_strlen(codon) >= 3 && 
            codon[0] == 'A' && codon[1] == 'T' && codon[2] == 'G');
}

int is_stop_codon(char *codon)
{
    if (!codon || my_strlen(codon) < 3)
        return 0;
    
    return ((codon[0] == 'T' && codon[1] == 'A' && codon[2] == 'A') ||
            (codon[0] == 'T' && codon[1] == 'A' && codon[2] == 'G') ||
            (codon[0] == 'T' && codon[1] == 'G' && codon[2] == 'A'));
}

void process_alignment(sequence_t *sequences)
{
    // Simple alignment implementation
    sequence_t *seq1 = sequences;
    sequence_t *seq2 = sequences ? sequences->next : NULL;
    
    if (!seq1 || !seq2) {
        printf("Error: Need exactly 2 sequences for alignment\n");
        return;
    }
    
    printf("Alignment of %s and %s:\n", seq1->id, seq2->id);
    printf("%s\n", seq1->data);
    printf("%s\n", seq2->data);
}