/*
** EPITECH PROJECT, 2025
** ScrabbleCalculator
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "scrabble.h"

Test(scrabble, basic_scores)
{
    cr_assert_eq(scrabble_score("quiz"), 22);
    cr_assert_eq(scrabble_score("cabbage"), 14);
    cr_assert_eq(scrabble_score("Java"), 14);
}

Test(scrabble, ignores_non_letters)
{
    cr_assert_eq(scrabble_score("hello-world!"), scrabble_score("helloworld"));
}
