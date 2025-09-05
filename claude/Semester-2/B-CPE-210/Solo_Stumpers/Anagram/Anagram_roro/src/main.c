/*
** EPITECH PROJECT, 2025
** Anagram
** File description:
** Main function for anagram
*/

#include "anagram.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        print_error();
        return 84;
    }
    return anagram_check(argv[1], argv[2]);
}