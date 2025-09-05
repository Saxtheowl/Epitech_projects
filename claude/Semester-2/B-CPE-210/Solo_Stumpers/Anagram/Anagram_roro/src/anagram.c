/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Main logic for anagram checking
*/

#include "anagram.h"

int anagram_check(char *str1, char *str2)
{
    if (!str1 || !str2)
        return 84;
    if (is_anagram(str1, str2)) {
        print_anagram();
        return 0;
    }
    print_no_anagram();
    return 0;
}