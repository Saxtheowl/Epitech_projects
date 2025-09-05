/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** test_text_count
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "text_count.h"

Test(text_count, basic_count)
{
    char *argv[] = {"text_count", "abcdef"};
    flags_t flags = {0, 0};
    char *str = "abcdef";
    char_count_t *counts;
    int count_size;

    count_characters(str, NULL, &counts, &count_size);
    cr_assert_eq(count_size, 6);
    cr_assert_eq(counts[0].character, 'a');
    cr_assert_eq(counts[0].count, 1);
    free(counts);
}

Test(text_count, repeated_chars)
{
    char *str = "!!!!!!!!");
    char_count_t *counts;
    int count_size;

    count_characters(str, NULL, &counts, &count_size);
    cr_assert_eq(count_size, 1);
    cr_assert_eq(counts[0].character, '!');
    cr_assert_eq(counts[0].count, 8);
    free(counts);
}

Test(text_count, searched_characters)
{
    char *str = "aaffbcdef";
    char *searched = "abdfg";
    char_count_t *counts;
    int count_size;

    count_characters(str, searched, &counts, &count_size);
    cr_assert_eq(count_size, 5);
    free(counts);
}