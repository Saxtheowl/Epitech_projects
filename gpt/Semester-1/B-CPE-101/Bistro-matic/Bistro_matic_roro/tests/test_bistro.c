/*
** EPITECH PROJECT, 2025
** Bistro_matic_roro
** File description:
** Basic tests
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "bistro.h"

Test(bistro, add_mul)
{
    char *r = eval_expr("0123456789", "()+-*/%", "2+3*4", 5);
    cr_assert_str_eq(r, "14");
    free(r);
}

Test(bistro, paren)
{
    char *r = eval_expr("0123456789", "()+-*/%", "(2+3)*4", 7);
    cr_assert_str_eq(r, "20");
    free(r);
}

Test(bistro, unary_and_divmod)
{
    char *r1 = eval_expr("0123456789", "()+-*/%", "-3+5", 4);
    char *r2 = eval_expr("0123456789", "()+-*/%", "10%3", 4);
    char *r3 = eval_expr("0123456789", "()+-*/%", "13/3", 4);
    cr_assert_str_eq(r1, "2");
    cr_assert_str_eq(r2, "1");
    cr_assert_str_eq(r3, "4");
    free(r1); free(r2); free(r3);
}
