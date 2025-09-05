/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** crocus
*/

#ifndef CROCUS_H_
    #define CROCUS_H_

    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>

    typedef struct args_s {
        char *number;
        char *string;
    } args_t;

    int crocus(int argc, char **argv);
    int parse_arguments(int argc, char **argv, args_t *args);
    void display_numbers(char *number, char *string);
    void print_digit(int digit, char character, int row);
    int is_valid_number(char *str);
    int my_strlen(char *str);

    extern char digit_patterns[10][5][6];

#endif /* !CROCUS_H_ */