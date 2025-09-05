/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Unit tests for scrabble calculator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "scrabble_calculator.h"

Test(scrabble_calculator, test_parse_letter_values)
{
    char values_str[] = "1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10";
    int *values = parse_letter_values(values_str);

    cr_assert_not_null(values);
    cr_assert_eq(values[0], 1);
    cr_assert_eq(values[1], 3);
    cr_assert_eq(values[25], 10);
    free(values);
}

Test(scrabble_calculator, test_is_valid_word)
{
    cr_assert_eq(is_valid_word("Hugo"), 1);
    cr_assert_eq(is_valid_word("Chocolatine"), 1);
    cr_assert_eq(is_valid_word("system32"), 0);
    cr_assert_eq(is_valid_word(""), 0);
    cr_assert_eq(is_valid_word(NULL), 0);
}

Test(scrabble_calculator, test_calculate_word_value)
{
    int values[] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

    cr_assert_eq(calculate_word_value("Hugo", values), 8);
    cr_assert_eq(calculate_word_value("Chocolatine", values), 18);
}

Test(scrabble_calculator, test_to_upper)
{
    cr_assert_eq(to_upper('a'), 'A');
    cr_assert_eq(to_upper('z'), 'Z');
    cr_assert_eq(to_upper('A'), 'A');
    cr_assert_eq(to_upper('Z'), 'Z');
}