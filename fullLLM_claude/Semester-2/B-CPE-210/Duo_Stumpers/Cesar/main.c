/*
** EPITECH PROJECT, 2024
** Cesar
** File description:
** Caesar cipher encoder implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void print_usage(void)
{
    fprintf(stderr, "Usage: ./cesar -f filename key OR ./cesar -s \"string\" key\n");
}

int is_valid_number(char *str)
{
    int i = 0;
    
    if (str[0] == '-' || str[0] == '+')
        i = 1;
    
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

char caesar_encrypt_char(char c, int key)
{
    if (c >= 'A' && c <= 'Z') {
        // For uppercase letters
        int shifted = ((c - 'A' + key) % 26 + 26) % 26;
        return 'A' + shifted;
    } else if (c >= 'a' && c <= 'z') {
        // For lowercase letters
        int shifted = ((c - 'a' + key) % 26 + 26) % 26;
        return 'a' + shifted;
    }
    // Non-alphabetic characters don't change
    return c;
}

int encrypt_file(char *filename, int key)
{
    FILE *input_file = fopen(filename, "r");
    FILE *output_file = fopen("crypt", "w");
    char c;
    
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return 84;
    }
    
    if (!output_file) {
        fprintf(stderr, "Error: Cannot create crypt file\n");
        if (input_file)
            fclose(input_file);
        return 84;
    }
    
    while ((c = fgetc(input_file)) != EOF) {
        fputc(caesar_encrypt_char(c, key), output_file);
    }
    
    fclose(input_file);
    fclose(output_file);
    
    // Set read-only permissions
    chmod("crypt", S_IRUSR | S_IRGRP | S_IROTH);
    
    return 0;
}

int encrypt_string(char *string, int key)
{
    FILE *output_file = fopen("crypt", "w");
    int i;
    
    if (!output_file) {
        fprintf(stderr, "Error: Cannot create crypt file\n");
        return 84;
    }
    
    for (i = 0; string[i]; i++) {
        fputc(caesar_encrypt_char(string[i], key), output_file);
    }
    
    fclose(output_file);
    
    // Set read-only permissions
    chmod("crypt", S_IRUSR | S_IRGRP | S_IROTH);
    
    return 0;
}

int main(int argc, char **argv)
{
    int key;
    
    if (argc != 4) {
        print_usage();
        return 84;
    }
    
    if (!is_valid_number(argv[3])) {
        print_usage();
        return 84;
    }
    
    key = atoi(argv[3]);
    
    if (strcmp(argv[1], "-f") == 0) {
        return encrypt_file(argv[2], key);
    } else if (strcmp(argv[1], "-s") == 0) {
        return encrypt_string(argv[2], key);
    } else {
        print_usage();
        return 84;
    }
}