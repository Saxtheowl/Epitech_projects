/*
** EPITECH PROJECT, 2025
** Dante Solver
** File description:
** Tests for parser/solver
*/

#include <criterion/criterion.h>
#include "dante.h"

Test(dante, simple_path)
{
    const char *raw = "***\n*X*\n***\n";
    maze_t *m = maze_from_string(raw);
    char *out = solve_maze(m);
    cr_assert_not_null(out);
    cr_assert_eq(out[0], 'o');
    cr_assert_eq(out[2], 'o');
    maze_destroy(m);
    free(out);
}

