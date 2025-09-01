/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Main function for FASTAtools project
*/

#include "fastatools.h"

int main(int ac, char **av)
{
    int option = 0;
    int k = 3;
    sequence_t *sequences;
    
    if (parse_arguments(ac, av, &option, &k) == 84) {
        return 84;
    }
    
    if (option == 0) {
        print_usage(0);
        return 0;
    }
    
    sequences = read_fasta();
    if (!sequences) {
        write(2, "Error reading FASTA input\n", 26);
        return 84;
    }
    
    switch (option) {
    case 1:
        process_dna(sequences);
        break;
    case 2:
        process_rna(sequences);
        break;
    case 3:
        process_reverse_complement(sequences);
        break;
    case 4:
        process_kmers(sequences, k);
        break;
    case 5:
        process_coding_sequences(sequences);
        break;
    case 6:
        process_amino_acids(sequences);
        break;
    case 7:
        process_alignment(sequences);
        break;
    default:
        write(2, "Invalid option\n", 15);
        free_sequences(sequences);
        return 84;
    }
    
    free_sequences(sequences);
    return 0;
}