/*
** EPITECH PROJECT, 2025
** BSQ_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "bsq.h"

Test(bsq, simple)
{
    map_t m;
    const char *rows[] = {
        ".....",
        "..o..",
        ".....",
        "....."
    };
    int i;

    m.rows = 4;
    m.cols = 5;
    m.grid = (char **)calloc(4, sizeof(char*));
    for (i = 0; i < 4; ++i)
        m.grid[i] = strdup(rows[i]);
    cr_assert_eq(solve_bsq(&m), 2);
    free_map(&m);
}
