#include "fastatools.h"

int compare_strings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

char **get_kmers(sequence_t *sequences, int k, int *count)
{
    char **kmers = malloc(10000 * sizeof(char *));
    int kmer_count = 0;
    int capacity = 10000;
    sequence_t *seq;
    
    if (!kmers) {
        *count = 0;
        return NULL;
    }
    
    for (seq = sequences; seq; seq = seq->next) {
        int seq_len = strlen(seq->data);
        int i;
        
        for (i = 0; i <= seq_len - k; i++) {
            char *kmer = malloc(k + 1);
            if (!kmer)
                continue;
            
            strncpy(kmer, seq->data + i, k);
            kmer[k] = '\0';
            
            // Check if kmer already exists
            int exists = 0;
            int j;
            for (j = 0; j < kmer_count; j++) {
                if (strcmp(kmers[j], kmer) == 0) {
                    exists = 1;
                    break;
                }
            }
            
            if (!exists) {
                if (kmer_count >= capacity) {
                    capacity *= 2;
                    kmers = realloc(kmers, capacity * sizeof(char *));
                }
                kmers[kmer_count] = kmer;
                kmer_count++;
            } else {
                free(kmer);
            }
        }
    }
    
    // Sort kmers alphabetically
    qsort(kmers, kmer_count, sizeof(char *), compare_strings);
    
    *count = kmer_count;
    return kmers;
}

static int is_start_codon(const char *codon)
{
    return strncmp(codon, "ATG", 3) == 0;
}

static int is_stop_codon(const char *codon)
{
    return strncmp(codon, "TAA", 3) == 0 || 
           strncmp(codon, "TAG", 3) == 0 || 
           strncmp(codon, "TGA", 3) == 0;
}

static void find_coding_sequences_in_strand(const char *seq, char ***coding_seqs, int *count, int *capacity)
{
    int seq_len = strlen(seq);
    int i;
    
    for (i = 0; i <= seq_len - 3; i++) {
        if (is_start_codon(seq + i)) {
            // Found start codon, look for stop codon
            int j;
            for (j = i + 3; j <= seq_len - 3; j += 3) {
                if (is_stop_codon(seq + j)) {
                    // Found coding sequence from i to j-1
                    int cs_len = j - i;  // Include start codon, exclude stop codon
                    char *coding_seq = malloc(cs_len + 1);
                    if (!coding_seq)
                        break;
                    
                    strncpy(coding_seq, seq + i, cs_len);
                    coding_seq[cs_len] = '\0';
                    
                    // Check if already exists
                    int exists = 0;
                    int k;
                    for (k = 0; k < *count; k++) {
                        if (strcmp((*coding_seqs)[k], coding_seq) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    
                    if (!exists) {
                        if (*count >= *capacity) {
                            *capacity *= 2;
                            *coding_seqs = realloc(*coding_seqs, *capacity * sizeof(char *));
                        }
                        (*coding_seqs)[*count] = coding_seq;
                        (*count)++;
                    } else {
                        free(coding_seq);
                    }
                    break;
                }
            }
        }
    }
}

char **get_coding_sequences(sequence_t *sequences, int *count)
{
    char **coding_seqs = malloc(1000 * sizeof(char *));
    int cs_count = 0;
    int capacity = 1000;
    sequence_t *seq;
    
    if (!coding_seqs) {
        *count = 0;
        return NULL;
    }
    
    for (seq = sequences; seq; seq = seq->next) {
        // Search in both strands
        find_coding_sequences_in_strand(seq->data, &coding_seqs, &cs_count, &capacity);
        
        char *rev_comp = get_reverse_complement(seq->data);
        if (rev_comp) {
            find_coding_sequences_in_strand(rev_comp, &coding_seqs, &cs_count, &capacity);
            free(rev_comp);
        }
    }
    
    // Sort alphabetically
    qsort(coding_seqs, cs_count, sizeof(char *), compare_strings);
    
    *count = cs_count;
    return coding_seqs;
}

char **get_amino_acids(sequence_t *sequences, int *count)
{
    char **amino_acids = malloc(1000 * sizeof(char *));
    int aa_count = 0;
    int capacity = 1000;
    int cs_count;
    char **coding_seqs = get_coding_sequences(sequences, &cs_count);
    int i;
    
    if (!amino_acids || !coding_seqs) {
        *count = 0;
        return NULL;
    }
    
    for (i = 0; i < cs_count; i++) {
        char *cs = coding_seqs[i];
        int cs_len = strlen(cs);
        char *amino_seq = malloc((cs_len / 3) + 1);
        int aa_idx = 0;
        int j;
        
        if (!amino_seq)
            continue;
        
        for (j = 0; j < cs_len - 2; j += 3) {
            char amino = codon_to_amino_acid(cs + j);
            if (amino != '?') {
                amino_seq[aa_idx] = amino;
                aa_idx++;
            }
        }
        amino_seq[aa_idx] = '\0';
        
        if (aa_idx > 0) {
            // Check if already exists
            int exists = 0;
            int k;
            for (k = 0; k < aa_count; k++) {
                if (strcmp(amino_acids[k], amino_seq) == 0) {
                    exists = 1;
                    break;
                }
            }
            
            if (!exists) {
                if (aa_count >= capacity) {
                    capacity *= 2;
                    amino_acids = realloc(amino_acids, capacity * sizeof(char *));
                }
                amino_acids[aa_count] = amino_seq;
                aa_count++;
            } else {
                free(amino_seq);
            }
        } else {
            free(amino_seq);
        }
    }
    
    // Free coding sequences
    for (i = 0; i < cs_count; i++) {
        free(coding_seqs[i]);
    }
    free(coding_seqs);
    
    // Sort alphabetically
    qsort(amino_acids, aa_count, sizeof(char *), compare_strings);
    
    *count = aa_count;
    return amino_acids;
}