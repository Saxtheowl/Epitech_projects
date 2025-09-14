#include "fastatools.h"

void clean_dna_sequence(char *seq)
{
    int i, j;
    
    for (i = 0, j = 0; seq[i]; i++) {
        char c = seq[i];
        
        // Convert to uppercase
        if (c >= 'a' && c <= 'z')
            c = c - 32;
        
        // Keep only valid DNA characters
        if (c == 'A' || c == 'T' || c == 'G' || c == 'C' || c == 'N') {
            seq[j] = c;
            j++;
        }
    }
    seq[j] = '\0';
}

char dna_complement(char c)
{
    switch (c) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'G': return 'C';
        case 'C': return 'G';
        case 'N': return 'N';
        default: return c;
    }
}

void reverse_string(char *str)
{
    int len = strlen(str);
    int i;
    
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

char *get_reverse_complement(const char *seq)
{
    int len = strlen(seq);
    char *result = malloc(len + 1);
    int i;
    
    if (!result)
        return NULL;
    
    for (i = 0; i < len; i++) {
        result[i] = dna_complement(seq[len - 1 - i]);
    }
    result[len] = '\0';
    
    return result;
}

char *dna_to_rna(const char *seq)
{
    int len = strlen(seq);
    char *result = malloc(len + 1);
    int i;
    
    if (!result)
        return NULL;
    
    for (i = 0; i < len; i++) {
        if (seq[i] == 'T') {
            result[i] = 'U';
        } else {
            result[i] = seq[i];
        }
    }
    result[len] = '\0';
    
    return result;
}

char codon_to_amino_acid(const char *codon)
{
    if (strncmp(codon, "GCT", 3) == 0 || strncmp(codon, "GCC", 3) == 0 || 
        strncmp(codon, "GCA", 3) == 0 || strncmp(codon, "GCG", 3) == 0) return 'A';
    
    if (strncmp(codon, "TGT", 3) == 0 || strncmp(codon, "TGC", 3) == 0) return 'C';
    
    if (strncmp(codon, "GAT", 3) == 0 || strncmp(codon, "GAC", 3) == 0) return 'D';
    
    if (strncmp(codon, "GAA", 3) == 0 || strncmp(codon, "GAG", 3) == 0) return 'E';
    
    if (strncmp(codon, "TTT", 3) == 0 || strncmp(codon, "TTC", 3) == 0) return 'F';
    
    if (strncmp(codon, "GGT", 3) == 0 || strncmp(codon, "GGC", 3) == 0 || 
        strncmp(codon, "GGA", 3) == 0 || strncmp(codon, "GGG", 3) == 0) return 'G';
    
    if (strncmp(codon, "CAT", 3) == 0 || strncmp(codon, "CAC", 3) == 0) return 'H';
    
    if (strncmp(codon, "ATT", 3) == 0 || strncmp(codon, "ATC", 3) == 0 || 
        strncmp(codon, "ATA", 3) == 0) return 'I';
    
    if (strncmp(codon, "AAA", 3) == 0 || strncmp(codon, "AAG", 3) == 0) return 'K';
    
    if (strncmp(codon, "TTA", 3) == 0 || strncmp(codon, "TTG", 3) == 0 || 
        strncmp(codon, "CTT", 3) == 0 || strncmp(codon, "CTC", 3) == 0 || 
        strncmp(codon, "CTA", 3) == 0 || strncmp(codon, "CTG", 3) == 0) return 'L';
    
    if (strncmp(codon, "ATG", 3) == 0) return 'M';
    
    if (strncmp(codon, "AAT", 3) == 0 || strncmp(codon, "AAC", 3) == 0) return 'N';
    
    if (strncmp(codon, "CCT", 3) == 0 || strncmp(codon, "CCC", 3) == 0 || 
        strncmp(codon, "CCA", 3) == 0 || strncmp(codon, "CCG", 3) == 0) return 'P';
    
    if (strncmp(codon, "CAA", 3) == 0 || strncmp(codon, "CAG", 3) == 0) return 'Q';
    
    if (strncmp(codon, "AGA", 3) == 0 || strncmp(codon, "AGG", 3) == 0 || 
        strncmp(codon, "CGT", 3) == 0 || strncmp(codon, "CGC", 3) == 0 || 
        strncmp(codon, "CGA", 3) == 0 || strncmp(codon, "CGG", 3) == 0) return 'R';
    
    if (strncmp(codon, "TCT", 3) == 0 || strncmp(codon, "TCC", 3) == 0 || 
        strncmp(codon, "TCA", 3) == 0 || strncmp(codon, "TCG", 3) == 0 || 
        strncmp(codon, "AGT", 3) == 0 || strncmp(codon, "AGC", 3) == 0) return 'S';
    
    if (strncmp(codon, "ACT", 3) == 0 || strncmp(codon, "ACC", 3) == 0 || 
        strncmp(codon, "ACA", 3) == 0 || strncmp(codon, "ACG", 3) == 0) return 'T';
    
    if (strncmp(codon, "GTT", 3) == 0 || strncmp(codon, "GTC", 3) == 0 || 
        strncmp(codon, "GTA", 3) == 0 || strncmp(codon, "GTG", 3) == 0) return 'V';
    
    if (strncmp(codon, "TGG", 3) == 0) return 'W';
    
    if (strncmp(codon, "TAT", 3) == 0 || strncmp(codon, "TAC", 3) == 0) return 'Y';
    
    // Check if codon contains N
    if (codon[0] == 'N' || codon[1] == 'N' || codon[2] == 'N') return 'X';
    
    return '?';  // Unknown codon
}