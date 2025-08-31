/*
** EPITECH PROJECT, 2025
** Dante Generator
** File description:
** Generation tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include "generator.h"

static int count_chars(const char *s, char c)
{
    int n = 0; int i = 0;
    while (s[i] != '\0') { if (s[i] == c) n++; i++; }
    return n;
}

Test(generator, basic_properties)
{
    char *m = generate_maze(10, 6, 1);
    cr_assert_not_null(m);
    /* only '*' 'X' and newlines */
    for (int i = 0; m[i] != '\0'; ++i)
        cr_assert((m[i] == '*' || m[i] == 'X' || m[i] == '\n'));
    /* dimensions: 6 lines, 5 newlines */
    cr_assert_eq(count_chars(m, '\n'), 5);
    /* entrance and exit open */
    cr_assert_eq(m[0], '*');
    cr_assert_eq(m[10*5 + 9], '*');
    free(m);
}

