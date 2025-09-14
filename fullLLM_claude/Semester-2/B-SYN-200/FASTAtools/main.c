#include "fastatools.h"

int main(int argc, char **argv)
{
    int option;
    int k = 0;
    
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        return 0;
    }
    
    if (argc < 2) {
        fprintf(stderr, "Error: Missing option\n");
        return 84;
    }
    
    option = atoi(argv[1]);
    if (option < 1 || option > 7) {
        fprintf(stderr, "Error: Invalid option\n");
        return 84;
    }
    
    if (option == 4) {
        if (argc < 3) {
            fprintf(stderr, "Error: Missing k parameter for option 4\n");
            return 84;
        }
        k = atoi(argv[2]);
        if (k <= 0) {
            fprintf(stderr, "Error: Invalid k parameter\n");
            return 84;
        }
    }
    
    return process_option(option, k);
}

void print_usage(void)
{
    printf("USAGE\n");
    printf("\t./FASTAtools option\n");
    printf("DESCRIPTION\n");
    printf("\toption 1: read FASTA from the standard input, write the DNA sequences to the\n");
    printf("\t\t  standard output\n");
    printf("\toption 2: read FASTA from the standard input, write the RNA sequences to the\n");
    printf("\t\t  standard output\n");
    printf("\toption 3: read FASTA from the standard input, write the reverse complement\n");
    printf("\t\t  to the standard output\n");
    printf("\toption 4: read FASTA from the standard input, write the k-mer list to the\n");
    printf("\t\t  standard output\n");
    printf("\toption 5: read FASTA from the standard input, write the coding sequences\n");
    printf("\t\t  list to the standard output\n");
    printf("\toption 6: read FASTA from the standard input, write the amino acids list to\n");
    printf("\t\t  the standard output\n");
    printf("\toption 7: read FASTA from the standard input containing exactly 2 squences,\n");
    printf("\t\t  align them and write the result to the standard output\n");
    printf("\tk: size of the k-mers for option 4\n");
}