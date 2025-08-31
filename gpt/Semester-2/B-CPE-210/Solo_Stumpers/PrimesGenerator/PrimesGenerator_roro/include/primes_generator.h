/*
** EPITECH PROJECT, 2025
** PrimesGenerator
** File description:
** Prototypes
*/

#ifndef PRIMES_GENERATOR_H
    #define PRIMES_GENERATOR_H

int parse_positive_int(const char *s, int *out);
int is_prime(int n);
int generate_primes_up_to(int n, int *out, int max);

#endif /* PRIMES_GENERATOR_H */

