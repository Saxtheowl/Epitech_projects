/*
** EPITECH PROJECT, 2024
** Crocus
** File description:
** ASCII art number display
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char *number;
    char *string;
} args_t;

// ASCII art patterns for digits 0-9 (5 rows each)
char *digit_patterns[10][5] = {
    // 0
    {"000", "0 0", "0 0", "0 0", "000"},
    // 1
    {"000", " 00", " 00", " 00", "0000"},
    // 2
    {"000", "  0", "000", "0  ", "0000"},
    // 3  
    {"0000", "   0", " 000", "   0", "0000"},
    // 4
    {"00", "0 0", "0000", "  0", "  0"},
    // 5
    {"00000", "0   ", "0000", "   0", "0000"},
    // 6
    {"000", "0 0", "0000", "0 0", "000"},
    // 7
    {"00000", "   0", "  0 ", " 0  ", "0   "},
    // 8
    {"000", "0 0", "000", "0 0", "000"},
    // 9
    {"000", "0 0", "0000", "  0", "000"}
};

void print_usage(void)
{
    fprintf(stderr, "Usage: ./crocus -n number [-s string]\n");
}

int is_number_string(char *str)
{
    int i;
    
    for (i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int parse_args(int argc, char **argv, args_t *args)
{
    int i = 1;
    
    args->number = NULL;
    args->string = "0";
    
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            args->number = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            args->string = argv[i + 1];
            i += 2;
        } else {
            print_usage();
            return 84;
        }
    }
    
    if (!args->number) {
        print_usage();
        return 84;
    }
    
    if (!is_number_string(args->number)) {
        return 84;
    }
    
    return 0;
}

char get_display_char(int digit, char *string)
{
    int string_len = strlen(string);
    if (string_len == 0)
        return '0';
    return string[digit % string_len];
}

void print_ascii_art(char *number, char *string)
{
    int num_len = strlen(number);
    int row, col;
    
    // Print each row (0-4) across all digits
    for (row = 0; row < 5; row++) {
        for (col = 0; col < num_len; col++) {
            int digit = number[col] - '0';
            char *pattern = digit_patterns[digit][row];
            char display_char = get_display_char(digit, string);
            int i;
            
            // Replace '0' with the appropriate character
            for (i = 0; pattern[i]; i++) {
                if (pattern[i] == '0') {
                    printf("%c", display_char);
                } else {
                    printf(" ");
                }
            }
            
            // Add space between digits (except for the last one)
            if (col < num_len - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    args_t args;
    
    if (parse_args(argc, argv, &args) != 0)
        return 84;
    
    print_ascii_art(args.number, args.string);
    
    return 0;
}