/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Utility functions
*/

#include "fastatools.h"

int my_strlen(char *str)
{
    int len = 0;
    
    if (!str)
        return 0;
    
    while (str[len])
        len++;
    
    return len;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;
    
    if (!s1 || !s2)
        return (s1 == s2) ? 0 : (s1 ? 1 : -1);
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    return s1[i] - s2[i];
}

char *my_strdup(char *src)
{
    char *dest;
    int i = 0;
    int len;
    
    if (!src)
        return NULL;
    
    len = my_strlen(src);
    dest = malloc(len + 1);
    if (!dest)
        return NULL;
    
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return dest;
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;
    
    if (!dest || !src)
        return dest;
    
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return dest;
}

char *my_strncpy(char *dest, char *src, int n)
{
    int i = 0;
    
    if (!dest || !src)
        return dest;
    
    while (i < n && src[i]) {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    
    return dest;
}

int is_valid_dna_char(char c)
{
    return (c == 'A' || c == 'a' || c == 'T' || c == 't' || 
            c == 'G' || c == 'g' || c == 'C' || c == 'c' || 
            c == 'N' || c == 'n');
}

char *clean_dna_sequence(char *sequence)
{
    char *clean;
    int i, j;
    int len;
    
    if (!sequence)
        return NULL;
    
    len = my_strlen(sequence);
    clean = malloc(len + 1);
    if (!clean)
        return NULL;
    
    j = 0;
    for (i = 0; i < len; i++) {
        if (is_valid_dna_char(sequence[i])) {
            if (sequence[i] >= 'a' && sequence[i] <= 'z')
                clean[j] = sequence[i] - 'a' + 'A';
            else
                clean[j] = sequence[i];
            j++;
        }
    }
    clean[j] = '\0';
    
    return clean;
}

void free_sequences(sequence_t *sequences)
{
    sequence_t *current = sequences;
    sequence_t *next;
    
    while (current) {
        next = current->next;
        if (current->id)
            free(current->id);
        if (current->data)
            free(current->data);
        free(current);
        current = next;
    }
}

void free_kmers(kmer_t *kmers)
{
    kmer_t *current = kmers;
    kmer_t *next;
    
    while (current) {
        next = current->next;
        if (current->kmer)
            free(current->kmer);
        free(current);
        current = next;
    }
}