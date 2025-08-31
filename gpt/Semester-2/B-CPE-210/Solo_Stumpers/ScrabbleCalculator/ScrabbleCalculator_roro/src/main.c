/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Main and logic
*/

#include <stdio.h>
#include <ctype.h>
#include "scrabble.h"

static int letter_value(char c)
{
    int u;

    if (!isalpha((unsigned char)c))
        return 0;
    u = toupper((unsigned char)c);
    if (u == 'Q' || u == 'Z')
        return 10;
    if (u == 'J' || u == 'X')
        return 8;
    if (u == 'K')
        return 5;
    if (u == 'F' || u == 'H' || u == 'V' || u == 'W' || u == 'Y')
        return 4;
    if (u == 'B' || u == 'C' || u == 'M' || u == 'P')
        return 3;
    if (u == 'D' || u == 'G')
        return 2;
    return 1;
}

int scrabble_score(const char *s)
{
    int sum;
    int i;

    sum = 0;
    i = 0;
    while (s[i] != '\0') {
        sum = sum + letter_value(s[i]);
        i = i + 1;
    }
    return sum;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    printf("%d\n", scrabble_score(argv[1]));
    return 0;
}

