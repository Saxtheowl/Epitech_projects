/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Header file for scrabble calculator
*/

#ifndef SCRABBLE_CALCULATOR_H_
    #define SCRABBLE_CALCULATOR_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>

    #define SUCCESS 0
    #define ERROR 84
    #define ALPHABET_SIZE 26

int *parse_letter_values(char *values_str);
int is_valid_word(char *word);
int calculate_word_value(char *word, int *letter_values);
char to_upper(char c);

#endif /* !SCRABBLE_CALCULATOR_H_ */