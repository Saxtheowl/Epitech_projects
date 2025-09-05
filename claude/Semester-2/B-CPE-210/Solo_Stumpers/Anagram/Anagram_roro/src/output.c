/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Output functions for anagram
*/

#include "anagram.h"

void print_anagram(void)
{
    write(1, "anagram!\n", 9);
}

void print_no_anagram(void)
{
    write(1, "no anagrams.\n", 13);
}

void print_error(void)
{
    write(2, "Error: not enough arguments.\n", 29);
}