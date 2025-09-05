/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** main
*/

#include "text_count.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        write(STDERR_FILENO, "Usage: ./text_count [-r] [-t] STR "
            "[SEARCHED_CHARACTERS]\n", 57);
        return 84;
    }
    return text_count(argc, argv);
}