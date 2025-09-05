/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Main logic for clean_str
*/

#include "clean_str.h"

int clean_str(char *str)
{
    int i = 0;
    int in_word = 0;
    int first_word = 1;

    if (!str) {
        my_putchar('\n');
        return 0;
    }
    while (str[i]) {
        if (!is_separator(str[i])) {
            if (!in_word) {
                if (!first_word)
                    my_putchar(' ');
                first_word = 0;
                in_word = 1;
            }
            my_putchar(str[i]);
        } else {
            in_word = 0;
        }
        i++;
    }
    my_putchar('\n');
    return 0;
}