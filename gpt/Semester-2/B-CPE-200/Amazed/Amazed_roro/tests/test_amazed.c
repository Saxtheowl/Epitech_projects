/*
** EPITECH PROJECT, 2025
** Amazed Solver
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "amazed.h"

Test(amazed, simple)
{
    const char *raw = "S..\n.#.\n..E\n";
    maze_t *m = maze_from_string(raw);
    char *out = solve_maze(m);
    cr_assert_not_null(out);
    cr_assert_eq(out[0], 'o');
    maze_destroy(m);
    free(out);
}

