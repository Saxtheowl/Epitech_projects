/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** K-mers processing functions
*/

#include "fastatools.h"

static kmer_t *create_kmer(char *kmer_str)
{
    kmer_t *kmer = malloc(sizeof(kmer_t));
    
    if (!kmer)
        return NULL;
    
    kmer->kmer = my_strdup(kmer_str);
    kmer->next = NULL;
    
    return kmer;
}

static int kmer_exists(kmer_t *kmers, char *kmer_str)
{
    kmer_t *current = kmers;
    
    while (current) {
        if (my_strcmp(current->kmer, kmer_str) == 0)
            return 1;
        current = current->next;
    }
    
    return 0;
}

void add_kmer(kmer_t **kmers, char *kmer_str)
{
    kmer_t *new_kmer;
    kmer_t *current;
    
    if (kmer_exists(*kmers, kmer_str))
        return;
    
    new_kmer = create_kmer(kmer_str);
    if (!new_kmer)
        return;
    
    if (*kmers == NULL) {
        *kmers = new_kmer;
        return;
    }
    
    current = *kmers;
    while (current->next)
        current = current->next;
    
    current->next = new_kmer;
}

kmer_t *extract_kmers(sequence_t *sequences, int k)
{
    kmer_t *kmers = NULL;
    sequence_t *current = sequences;
    char *kmer_str;
    int i, seq_len;
    
    kmer_str = malloc(k + 1);
    if (!kmer_str)
        return NULL;
    
    while (current) {
        seq_len = my_strlen(current->data);
        for (i = 0; i <= seq_len - k; i++) {
            my_strncpy(kmer_str, current->data + i, k);
            kmer_str[k] = '\0';
            add_kmer(&kmers, kmer_str);
        }
        current = current->next;
    }
    
    free(kmer_str);
    return kmers;
}

void sort_kmers(kmer_t **kmers)
{
    kmer_t *current, *next, *prev;
    int swapped = 1;
    
    if (!kmers || !*kmers)
        return;
    
    while (swapped) {
        swapped = 0;
        current = *kmers;
        prev = NULL;
        
        while (current->next) {
            next = current->next;
            
            if (my_strcmp(current->kmer, next->kmer) > 0) {
                // Swap nodes
                if (prev)
                    prev->next = next;
                else
                    *kmers = next;
                
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

void process_kmers(sequence_t *sequences, int k)
{
    kmer_t *kmers = extract_kmers(sequences, k);
    kmer_t *current;
    
    if (!kmers)
        return;
    
    sort_kmers(&kmers);
    
    current = kmers;
    while (current) {
        printf("%s\n", current->kmer);
        current = current->next;
    }
    
    free_kmers(kmers);
}