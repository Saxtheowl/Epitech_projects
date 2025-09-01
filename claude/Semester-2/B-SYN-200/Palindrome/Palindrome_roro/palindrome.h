/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Header file for palindrome project
*/

#ifndef PALINDROME_H_
#define PALINDROME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int number;
    int palindrome;
    int base;
    int imin;
    int imax;
    int mode; // 0 for -n, 1 for -p
} params_t;

// Required functions
int my_factrec_synthesis(int nb);
int my_squareroot_synthesis(int nb);

// Main functions
int parse_arguments(int ac, char **av, params_t *params);
void print_usage(void);
int is_palindrome(long number, int base);
long reverse_number(long number, int base);
int find_palindrome(long number, int base, int max_iterations);
void process_number_mode(params_t *params);
void process_palindrome_mode(params_t *params);

// Utility functions
int my_strlen(char *str);
int my_atoi(char *str);
int is_valid_number(char *str);

#endif /* !PALINDROME_H_ */