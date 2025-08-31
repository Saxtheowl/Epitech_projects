/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "text_count.h"

Test(textcount, basic_counts)
{
    int l;
    int w;
    int c;

    count_text("hello world", &l, &w, &c);
    cr_assert_eq(l, 1);
    cr_assert_eq(w, 2);
    cr_assert_eq(c, 11);
}

Test(textcount, multiline)
{
    int l; int w; int c;
    count_text("one\n two\nthree\n", &l, &w, &c);
    cr_assert_eq(l, 3);
    cr_assert_eq(w, 3);
    cr_assert_eq(c, 13);
}
