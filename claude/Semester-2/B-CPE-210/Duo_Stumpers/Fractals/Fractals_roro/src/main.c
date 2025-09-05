/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** main
*/

#include "fractals.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        write(STDERR_FILENO, "Usage: ./fractals ITERATIONS SHARP_PATTERN "
            "DOT_PATTERN\n", 56);
        return 84;
    }
    return fractals(argc, argv);
}