/*
** EPITECH PROJECT, 2025
** GpaCalculator
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "gpa.h"

Test(gpa, average)
{
    double avg;

    cr_assert(parse_grades("A A- B+", &avg));
    cr_assert_float_eq(avg, (4.0 + 3.7 + 3.3) / 3.0, 0.0001);
}

Test(gpa, invalid_grades)
{
    double avg;
    cr_assert_not(parse_grades("Z+", &avg));
    cr_assert_not(parse_grades("A, , B", &avg));
}
