/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Anagram logic functions
*/

#include "anagram.h"

void count_chars(char const *str, int *count)
{
    int i = 0;

    while (str[i]) {
        count[(unsigned char)to_lower(str[i])]++;
        i++;
    }
}

int compare_counts(int *count)
{
    int i = 0;

    while (i < ASCII_SIZE) {
        if (count[i] != 0)
            return 0;
        i++;
    }
    return 1;
}

int is_anagram(char const *str1, char const *str2)
{
    int count[ASCII_SIZE] = {0};
    int i = 0;

    if (!str1 || !str2)
        return 0;
    while (str1[i]) {
        count[(unsigned char)to_lower(str1[i])]++;
        i++;
    }
    i = 0;
    while (str2[i]) {
        count[(unsigned char)to_lower(str2[i])]--;
        i++;
    }
    return compare_counts(count);
}