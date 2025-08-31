/*
** EPITECH PROJECT, 2025
** Amazed Solver
** File description:
** Unsolvable maze test
*/

#include <criterion/criterion.h>
#include "amazed.h"

Test(amazed, unsolvable)
{
    const char *raw = "S#\n#E\n";
    maze_t *m = maze_from_string(raw);
    char *out = solve_maze(m);
    cr_assert_null(out);
    maze_destroy(m);
}

