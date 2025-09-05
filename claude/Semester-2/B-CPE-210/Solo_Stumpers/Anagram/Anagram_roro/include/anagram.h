/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Header file for anagram project
*/

#ifndef ANAGRAM_H_
    #define ANAGRAM_H_

    #include <unistd.h>

    #define ASCII_SIZE 256

// Main function
int anagram_check(char *str1, char *str2);

// Utility functions
int my_strlen(char const *str);
char to_lower(char c);

// Anagram logic functions
int is_anagram(char const *str1, char const *str2);
void count_chars(char const *str, int *count);
int compare_counts(int *count);

// Output functions
void print_anagram(void);
void print_no_anagram(void);
void print_error(void);

#endif /* !ANAGRAM_H_ */