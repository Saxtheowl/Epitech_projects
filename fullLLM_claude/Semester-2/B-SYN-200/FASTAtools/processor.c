#include "fastatools.h"

int process_option(int option, int k)
{
    sequence_t *sequences = parse_fasta(stdin);
    sequence_t *seq;
    int i;
    
    if (!sequences) {
        fprintf(stderr, "Error: Could not parse FASTA input\n");
        return 84;
    }
    
    switch (option) {
        case 1: // DNA sequences
            for (seq = sequences; seq; seq = seq->next) {
                printf("%s\n", seq->id);
                printf("%s\n", seq->data);
            }
            break;
            
        case 2: // RNA sequences
            for (seq = sequences; seq; seq = seq->next) {
                char *rna = dna_to_rna(seq->data);
                printf("%s\n", seq->id);
                printf("%s\n", rna);
                free(rna);
            }
            break;
            
        case 3: // Reverse complement
            for (seq = sequences; seq; seq = seq->next) {
                char *rev_comp = get_reverse_complement(seq->data);
                printf("%s\n", seq->id);
                printf("%s\n", rev_comp);
                free(rev_comp);
            }
            break;
            
        case 4: // K-mers
            {
                int count;
                char **kmers = get_kmers(sequences, k, &count);
                for (i = 0; i < count; i++) {
                    printf("%s\n", kmers[i]);
                    free(kmers[i]);
                }
                free(kmers);
            }
            break;
            
        case 5: // Coding sequences
            {
                int count;
                char **coding_seqs = get_coding_sequences(sequences, &count);
                for (i = 0; i < count; i++) {
                    printf("%s\n", coding_seqs[i]);
                    free(coding_seqs[i]);
                }
                free(coding_seqs);
            }
            break;
            
        case 6: // Amino acids
            {
                int count;
                char **amino_acids = get_amino_acids(sequences, &count);
                for (i = 0; i < count; i++) {
                    printf("%s\n", amino_acids[i]);
                    free(amino_acids[i]);
                }
                free(amino_acids);
            }
            break;
            
        case 7: // DNA alignment (simplified implementation)
            {
                sequence_t *seq1 = sequences;
                sequence_t *seq2 = sequences ? sequences->next : NULL;
                
                if (!seq1 || !seq2) {
                    fprintf(stderr, "Error: Need exactly 2 sequences for alignment\n");
                    free_sequences(sequences);
                    return 84;
                }
                
                printf("Sequence 1: %s\n", seq1->data);
                printf("Sequence 2: %s\n", seq2->data);
                // Simplified alignment - just output the sequences
            }
            break;
            
        default:
            fprintf(stderr, "Error: Invalid option\n");
            free_sequences(sequences);
            return 84;
    }
    
    free_sequences(sequences);
    return 0;
}