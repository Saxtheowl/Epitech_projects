/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Main function for scrabble calculator
*/

#include "scrabble_calculator.h"

int main(int argc, char **argv)
{
    int *letter_values = NULL;
    int word_value = 0;

    if (argc != 3)
        return ERROR;
    if (!argv[2] || argv[2][0] == '\0')
        return ERROR;
    letter_values = parse_letter_values(argv[1]);
    if (!letter_values)
        return ERROR;
    if (!is_valid_word(argv[2])) {
        free(letter_values);
        return ERROR;
    }
    word_value = calculate_word_value(argv[2], letter_values);
    printf("%d\n", word_value);
    free(letter_values);
    return SUCCESS;
}