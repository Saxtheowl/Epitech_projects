/*
** EPITECH PROJECT, 2025
** FASTAtools
** File description:
** Argument parsing and FASTA file reading
*/

#include "fastatools.h"

static int is_number(char *str)
{
    int i = 0;
    
    if (!str || !str[0])
        return 0;
    
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

static int my_atoi(char *str)
{
    int result = 0;
    int i = 0;
    
    if (!str)
        return 0;
    
    while (str[i] && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result;
}

int parse_arguments(int ac, char **av, int *option, int *k)
{
    if (ac < 2) {
        *option = 0;
        return 0;
    }
    
    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        *option = 0;
        return 0;
    }
    
    if (!is_number(av[1])) {
        return 84;
    }
    
    *option = my_atoi(av[1]);
    
    if (*option < 1 || *option > 7) {
        return 84;
    }
    
    if (*option == 4) {
        if (ac < 3 || !is_number(av[2])) {
            return 84;
        }
        *k = my_atoi(av[2]);
        if (*k <= 0) {
            return 84;
        }
    }
    
    return 0;
}

void print_usage(int k_option)
{
    (void)k_option;
    printf("USAGE\n");
    printf("    ./FASTAtools option\n");
    printf("DESCRIPTION\n");
    printf("    option 1: read FASTA from the standard input, write the DNA sequences to the\n");
    printf("              standard output\n");
    printf("    option 2: read FASTA from the standard input, write the RNA sequences to the\n");
    printf("              standard output\n");
    printf("    option 3: read FASTA from the standard input, write the reverse complement\n");
    printf("              to the standard output\n");
    printf("    option 4: read FASTA from the standard input, write the k-mer list to the\n");
    printf("              standard output\n");
    printf("    option 5: read FASTA from the standard input, write the coding sequences\n");
    printf("              list to the standard output\n");
    printf("    option 6: read FASTA from the standard input, write the amino acids list to\n");
    printf("              the standard output\n");
    printf("    option 7: read FASTA from the standard input containing exactly 2 squences,\n");
    printf("              align them and write the result to the standard output\n");
    printf("    k: size of the k-mers for option 4\n");
}

static sequence_t *create_sequence(char *id, char *data)
{
    sequence_t *seq = malloc(sizeof(sequence_t));
    
    if (!seq)
        return NULL;
    
    seq->id = my_strdup(id);
    seq->data = my_strdup(data);
    seq->next = NULL;
    
    return seq;
}

sequence_t *read_fasta(void)
{
    char buffer[BUFFER_SIZE];
    char current_id[BUFFER_SIZE] = {0};
    char current_data[BUFFER_SIZE * 10] = {0};
    sequence_t *head = NULL;
    sequence_t *current = NULL;
    int has_id = 0;
    
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        // Remove newline
        int len = my_strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        if (buffer[0] == '>') {
            // New sequence identifier
            if (has_id && my_strlen(current_data) > 0) {
                // Save previous sequence
                sequence_t *new_seq = create_sequence(current_id, current_data);
                if (head == NULL) {
                    head = new_seq;
                    current = new_seq;
                } else {
                    current->next = new_seq;
                    current = new_seq;
                }
            }
            // Start new sequence
            my_strcpy(current_id, buffer + 1);
            current_data[0] = '\0';
            has_id = 1;
        } else if (has_id && buffer[0] != '\0') {
            // Sequence data
            char *clean_line = clean_dna_sequence(buffer);
            if (clean_line && my_strlen(clean_line) > 0) {
                int data_len = my_strlen(current_data);
                int line_len = my_strlen(clean_line);
                if (data_len + line_len < BUFFER_SIZE * 10 - 1) {
                    my_strcpy(current_data + data_len, clean_line);
                }
                free(clean_line);
            }
        }
    }
    
    // Save last sequence
    if (has_id && my_strlen(current_data) > 0) {
        sequence_t *new_seq = create_sequence(current_id, current_data);
        if (head == NULL) {
            head = new_seq;
        } else {
            current->next = new_seq;
        }
    }
    
    return head;
}