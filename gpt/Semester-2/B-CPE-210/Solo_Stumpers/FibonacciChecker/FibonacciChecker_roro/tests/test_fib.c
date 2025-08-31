/*
** EPITECH PROJECT, 2025
** FibonacciChecker
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "fib_checker.h"

Test(fibonacci, small_values)
{
    cr_assert(is_fibonacci(0));
    cr_assert(is_fibonacci(1));
    cr_assert(is_fibonacci(2));
    cr_assert(is_fibonacci(3));
    cr_assert_not(is_fibonacci(4));
    cr_assert(is_fibonacci(5));
}

Test(fibonacci, larger_numbers)
{
    cr_assert(is_fibonacci(34));
    cr_assert_not(is_fibonacci(35));
}
