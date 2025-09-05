/*
** EPITECH PROJECT, 2025
** SortWords
** File description:
** Main function for sort_words
*/

#include "sort_words.h"

int main(int argc, char **argv)
{
    if (argc == 1) {
        my_putchar('\n');
        return 0;
    }
    if (argc != 2)
        return 84;
    return sort_words(argv[1]);
}