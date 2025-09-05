/*
** EPITECH PROJECT, 2025
** CleanStr
** File description:
** Main function for clean_str
*/

#include "clean_str.h"

int main(int argc, char **argv)
{
    if (argc == 1) {
        my_putchar('\n');
        return 0;
    }
    if (argc != 2)
        return 84;
    return clean_str(argv[1]);
}