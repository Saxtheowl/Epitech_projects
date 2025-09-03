/*
** EPITECH PROJECT, 2024
** math_functions.c
** File description:
** mathematical functions
*/

#include "../../include/my.h"

int my_compute_power_rec(int nb, int power)
{
    if (power < 0)
        return 0;
    if (power == 0)
        return 1;
    return nb * my_compute_power_rec(nb, power - 1);
}

int my_compute_square_root(int nb)
{
    int i = 0;

    if (nb < 0)
        return 0;
    if (nb == 0 || nb == 1)
        return nb;
    while (i * i <= nb) {
        if (i * i == nb)
            return i;
        i++;
    }
    return 0;
}

int my_is_prime(int nb)
{
    int i = 3;

    if (nb <= 1)
        return 0;
    if (nb == 2)
        return 1;
    if (nb % 2 == 0)
        return 0;
    while (i * i <= nb) {
        if (nb % i == 0)
            return 0;
        i += 2;
    }
    return 1;
}

int my_find_prime_sup(int nb)
{
    if (nb < 2)
        return 2;
    while (!my_is_prime(nb))
        nb++;
    return nb;
}