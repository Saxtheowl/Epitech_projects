/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Coding sequences and amino acids processing
*/

#include "fastatools.h"

static sequence_t *create_coding_sequence(char *data)
{
    sequence_t *seq = malloc(sizeof(sequence_t));
    
    if (!seq)
        return NULL;
    
    seq->id = NULL;
    seq->data = my_strdup(data);
    seq->next = NULL;
    
    return seq;
}

static void add_coding_sequence(sequence_t **coding_seqs, char *data)
{
    sequence_t *new_seq = create_coding_sequence(data);
    sequence_t *current;
    
    if (!new_seq)
        return;
    
    if (*coding_seqs == NULL) {
        *coding_seqs = new_seq;
        return;
    }
    
    current = *coding_seqs;
    while (current->next)
        current = current->next;
    
    current->next = new_seq;
}

static void find_coding_in_sequence(char *sequence, sequence_t **coding_seqs)
{
    int len = my_strlen(sequence);
    int i;
    char codon[4];
    
    codon[3] = '\0';
    
    // Check all reading frames (0, 1, 2)
    for (int frame = 0; frame < 3; frame++) {
        for (i = frame; i <= len - 3; i += 3) {
            my_strncpy(codon, sequence + i, 3);
            
            if (is_start_codon(codon)) {
                // Found start codon, look for stop codon
                int start_pos = i;
                int j;
                
                for (j = i + 3; j <= len - 3; j += 3) {
                    my_strncpy(codon, sequence + j, 3);
                    if (is_stop_codon(codon)) {
                        // Found complete coding sequence (excluding stop codon)
                        int coding_len = j - start_pos;
                        if (coding_len > 0) {
                            char *coding_seq = malloc(coding_len + 1);
                            if (coding_seq) {
                                my_strncpy(coding_seq, sequence + start_pos, coding_len);
                                coding_seq[coding_len] = '\0';
                                add_coding_sequence(coding_seqs, coding_seq);
                                free(coding_seq);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

sequence_t *find_coding_sequences(sequence_t *sequences)
{
    sequence_t *coding_seqs = NULL;
    sequence_t *current = sequences;
    
    while (current) {
        // Find coding sequences in forward strand
        find_coding_in_sequence(current->data, &coding_seqs);
        
        // Find coding sequences in reverse complement
        char *rev_comp = reverse_complement(current->data);
        if (rev_comp) {
            find_coding_in_sequence(rev_comp, &coding_seqs);
            free(rev_comp);
        }
        
        current = current->next;
    }
    
    return coding_seqs;
}

static void sort_sequences(sequence_t **sequences)
{
    sequence_t *current, *next, *prev;
    int swapped = 1;
    
    if (!sequences || !*sequences)
        return;
    
    while (swapped) {
        swapped = 0;
        current = *sequences;
        prev = NULL;
        
        while (current->next) {
            next = current->next;
            
            if (my_strcmp(current->data, next->data) > 0) {
                // Swap nodes
                if (prev)
                    prev->next = next;
                else
                    *sequences = next;
                
                current->next = next->next;
                next->next = current;
                
                swapped = 1;
                prev = next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}

void process_coding_sequences(sequence_t *sequences)
{
    sequence_t *coding_seqs = find_coding_sequences(sequences);
    sequence_t *current;
    
    if (!coding_seqs)
        return;
    
    sort_sequences(&coding_seqs);
    
    current = coding_seqs;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
    
    free_sequences(coding_seqs);
}

char *translate_to_amino_acid(char *codon)
{
    if (!codon || my_strlen(codon) < 3)
        return my_strdup("X");
    
    // Check for N in codon
    if (codon[0] == 'N' || codon[1] == 'N' || codon[2] == 'N')
        return my_strdup("X");
    
    // Amino acid translation table
    if ((codon[0] == 'G' && codon[1] == 'C') ||
        (codon[0] == 'G' && codon[1] == 'C'))
        return my_strdup("A");
    if ((codon[0] == 'T' && codon[1] == 'G' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("C");
    if ((codon[0] == 'G' && codon[1] == 'A' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("D");
    if ((codon[0] == 'G' && codon[1] == 'A' && (codon[2] == 'A' || codon[2] == 'G')))
        return my_strdup("E");
    if ((codon[0] == 'T' && codon[1] == 'T' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("F");
    if (codon[0] == 'G' && codon[1] == 'G')
        return my_strdup("G");
    if ((codon[0] == 'C' && codon[1] == 'A' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("H");
    if (codon[0] == 'A' && codon[1] == 'T' && (codon[2] == 'T' || codon[2] == 'C' || codon[2] == 'A'))
        return my_strdup("I");
    if ((codon[0] == 'A' && codon[1] == 'A' && (codon[2] == 'A' || codon[2] == 'G')))
        return my_strdup("K");
    if ((codon[0] == 'T' && codon[1] == 'T' && (codon[2] == 'A' || codon[2] == 'G')) ||
        (codon[0] == 'C' && codon[1] == 'T'))
        return my_strdup("L");
    if (codon[0] == 'A' && codon[1] == 'T' && codon[2] == 'G')
        return my_strdup("M");
    if ((codon[0] == 'A' && codon[1] == 'A' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("N");
    if (codon[0] == 'C' && codon[1] == 'C')
        return my_strdup("P");
    if ((codon[0] == 'C' && codon[1] == 'A' && (codon[2] == 'A' || codon[2] == 'G')))
        return my_strdup("Q");
    if ((codon[0] == 'A' && codon[1] == 'G' && (codon[2] == 'A' || codon[2] == 'G')) ||
        (codon[0] == 'C' && codon[1] == 'G'))
        return my_strdup("R");
    if ((codon[0] == 'T' && codon[1] == 'C') ||
        (codon[0] == 'A' && codon[1] == 'G' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("S");
    if (codon[0] == 'A' && codon[1] == 'C')
        return my_strdup("T");
    if (codon[0] == 'G' && codon[1] == 'T')
        return my_strdup("V");
    if (codon[0] == 'T' && codon[1] == 'G' && codon[2] == 'G')
        return my_strdup("W");
    if ((codon[0] == 'T' && codon[1] == 'A' && (codon[2] == 'T' || codon[2] == 'C')))
        return my_strdup("Y");
    
    return my_strdup("X");
}

void process_amino_acids(sequence_t *sequences)
{
    sequence_t *coding_seqs = find_coding_sequences(sequences);
    sequence_t *current = coding_seqs;
    kmer_t *amino_acids = NULL;
    char codon[4];
    int i;
    
    codon[3] = '\0';
    
    while (current) {
        int len = my_strlen(current->data);
        char *amino_sequence = malloc((len / 3) + 1);
        int amino_pos = 0;
        
        if (amino_sequence) {
            // Skip start codon and translate until stop codon
            for (i = 3; i <= len - 6; i += 3) {  // Skip start codon, stop before stop codon
                my_strncpy(codon, current->data + i, 3);
                if (is_stop_codon(codon))
                    break;
                
                char *amino = translate_to_amino_acid(codon);
                if (amino) {
                    amino_sequence[amino_pos] = amino[0];
                    amino_pos++;
                    free(amino);
                }
            }
            amino_sequence[amino_pos] = '\0';
            
            if (amino_pos > 0) {
                add_kmer(&amino_acids, amino_sequence);
            }
            free(amino_sequence);
        }
        
        current = current->next;
    }
    
    if (amino_acids) {
        sort_kmers(&amino_acids);
        
        kmer_t *amino_current = amino_acids;
        while (amino_current) {
            printf("%s\n", amino_current->kmer);
            amino_current = amino_current->next;
        }
        
        free_kmers(amino_acids);
    }
    
    free_sequences(coding_seqs);
}