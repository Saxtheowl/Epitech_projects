#ifndef PALINDROME_H
#define PALINDROME_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int n;
    int p;
    int base;
    int imin;
    int imax;
    int mode_n;  // 1 if -n mode, 0 if -p mode
} config_t;

// Argument parsing
int parse_args(int argc, char **argv, config_t *config);
void print_usage(void);

// Number operations in different bases
long long reverse_number(long long num, int base);
int is_palindrome(long long num, int base);
long long add_numbers(long long num1, long long num2);
int find_palindrome_iterations(int n, int base, int max_iter);
int find_iterations_to_target(int n, int target, int base, int max_iter);

// Main functionality
void process_n_mode(config_t *config);
void process_p_mode(config_t *config);

// Utility functions
int is_valid_number(char *str);
void print_error(char *message);

#endif