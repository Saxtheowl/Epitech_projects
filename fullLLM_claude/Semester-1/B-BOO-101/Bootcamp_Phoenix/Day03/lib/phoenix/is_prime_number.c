/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** is_prime_number.c
*/

int is_prime_number(int nb)
{
    int i;

    if (nb <= 1)
        return 0;

    if (nb == 2)
        return 1;

    if (nb % 2 == 0)
        return 0;

    for (i = 3; i * i <= nb; i += 2) {
        if (nb % i == 0)
            return 0;
    }

    return 1;
}