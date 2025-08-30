/*
** EPITECH PROJECT, 2025
** Count_island_roro
** File description:
** Basic Criterion tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "count_island.h"

static map_t map_from(const char **lines, int n)
{
    map_t m;
    int i;

    m.rows = n;
    m.cols = (int)strlen(lines[0]);
    m.grid = calloc((size_t)n, sizeof(char *));
    for (i = 0; i < n; ++i)
        m.grid[i] = strdup(lines[i]);
    return m;
}

Test(island, small_map)
{
    const char *src[] = {
        "..XX.",
        ".X..X",
        "..XX."
    };
    const char *exp[] = {
        "..00.",
        ".0..1",
        "..11."
    };
    map_t m = map_from(src, 3);
    int count = label_islands(&m);
    cr_assert_eq(count, 2);
    cr_assert_str_eq(m.grid[0], exp[0]);
    cr_assert_str_eq(m.grid[1], exp[1]);
    cr_assert_str_eq(m.grid[2], exp[2]);
    free_map(&m);
}

