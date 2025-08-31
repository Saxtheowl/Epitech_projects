/*
** EPITECH PROJECT, 2025
** Dante Solver
** File description:
** Unsolvable maze test
*/

#include <criterion/criterion.h>
#include "dante.h"

Test(dante, unsolvable)
{
    const char *raw = "X*\nXX\n";
    maze_t *m = maze_from_string(raw);
    char *out = solve_maze(m);
    cr_assert_null(out);
    maze_destroy(m);
}

