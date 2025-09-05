/*
** EPITECH PROJECT, 2025
** Crocus
** File description:
** display
*/

#include "crocus.h"

void print_digit(int digit, char character, int row)
{
    int i = 0;

    while (digit_patterns[digit][row][i] != '\0') {
        if (digit_patterns[digit][row][i] == 'X')
            printf("%c", character);
        else
            printf(" ");
        i++;
    }
}

void display_numbers(char *number, char *string)
{
    int row = 0;
    int i = 0;
    int string_len = my_strlen(string);

    for (row = 0; row < 5; row++) {
        for (i = 0; number[i]; i++) {
            int digit = number[i] - '0';
            char character = string[digit % string_len];
            
            print_digit(digit, character, row);
            if (number[i + 1])
                printf(" ");
        }
        printf("\n");
    }
}