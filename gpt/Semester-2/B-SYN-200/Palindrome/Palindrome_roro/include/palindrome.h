/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Prototypes
*/

#ifndef PALINDROME_H
    #define PALINDROME_H

int parse_args(int argc, char **argv, long *n, int *base, int *imax);
int is_palindrome_base(long n, int base);
long reverse_in_base(long n, int base);
long add_reverse_step(long n, int base);
int find_palindrome(long n, int base, int imax, long *res, int *iters);

#endif /* PALINDROME_H */

