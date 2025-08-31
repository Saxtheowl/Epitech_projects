/*
** EPITECH PROJECT, 2025
** GameOfLife
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include "game_of_life.h"

Test(gol, blinker_oscillator)
{
    const int rows = 3;
    const int cols = 3;
    const char *g1 = ".X."
                      ".X."
                      ".X.";
    char out[rows * cols + 1];

    step_grid(g1, out, rows, cols);
    cr_assert_str_eq(out, "...XXX...");
}

Test(gol, still_life_block)
{
    const int rows = 4;
    const int cols = 4;
    const char *g =
        "...."
        ".XX."
        ".XX."
        "....";
    char out[rows * cols + 1];
    step_grid(g, out, rows, cols);
    /* remains identical */
    cr_assert_str_eq(out, g);
}
