/*
** EPITECH PROJECT, 2025
** Fractals
** File description:
** fractals
*/

#include "fractals.h"

int fractals(int argc, char **argv)
{
    int iterations = 0;
    pattern_t sharp_pattern;
    pattern_t dot_pattern;

    if (parse_arguments(argc, argv, &iterations, &sharp_pattern, 
        &dot_pattern) != 0) {
        write(STDERR_FILENO, "Invalid arguments\n", 18);
        return 84;
    }
    generate_fractal(iterations, sharp_pattern, dot_pattern);
    free_pattern(&sharp_pattern);
    free_pattern(&dot_pattern);
    return 0;
}