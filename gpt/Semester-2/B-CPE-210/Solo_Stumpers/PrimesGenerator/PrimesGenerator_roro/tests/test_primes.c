/*
** EPITECH PROJECT, 2025
** PrimesGenerator
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "primes_generator.h"

Test(primes, is_prime_basic)
{
    cr_assert_not(is_prime(1));
    cr_assert(is_prime(2));
    cr_assert(is_prime(3));
    cr_assert_not(is_prime(4));
    cr_assert(is_prime(5));
}

Test(primes, generate_small)
{
    int out[16];
    int c;

    c = generate_primes_up_to(10, out, 16);
    cr_assert_eq(c, 4);
    cr_assert_eq(out[0], 2);
    cr_assert_eq(out[1], 3);
    cr_assert_eq(out[2], 5);
    cr_assert_eq(out[3], 7);
}

Test(primes, edge_cases)
{
    int out[8];
    cr_assert_not(is_prime(0));
    cr_assert_not(is_prime(1));
    cr_assert(is_prime(2));
    cr_assert_not(is_prime(9));
    cr_assert_eq(generate_primes_up_to(1, out, 8), 0);
}
