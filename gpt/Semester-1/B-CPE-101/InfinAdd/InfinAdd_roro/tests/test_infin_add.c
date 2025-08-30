/*
** EPITECH PROJECT, 2025
** InfinAdd_roro
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <stdlib.h>
#include "infin_add.h"

Test(infin_add, basics)
{
    char *r = infin_add("123", "877");
    cr_assert_str_eq(r, "1000");
    free(r);
}

Test(infin_add, signs)
{
    char *r1 = infin_add("-5", "2");
    char *r2 = infin_add("7", "-7");
    char *r3 = infin_add("-3", "-4");
    cr_assert_str_eq(r1, "-3");
    cr_assert_str_eq(r2, "0");
    cr_assert_str_eq(r3, "-7");
    free(r1); free(r2); free(r3);
}
