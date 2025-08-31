/*
** EPITECH PROJECT, 2025
** Malloc
** File description:
**   Minimal sanity tests
*/

#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>

Test(basic, alloc_free)
{
    char *p = malloc(32);
    cr_assert_neq(p, NULL);
    strcpy(p, "hello");
    cr_assert_str_eq(p, "hello");
    free(p);
}

