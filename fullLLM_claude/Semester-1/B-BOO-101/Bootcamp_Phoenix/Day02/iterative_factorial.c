/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** iterative_factorial.c
*/

int iterative_factorial(int nb)
{
    int result = 1;
    int i;

    if (nb < 0)
        return 0;

    if (nb == 0)
        return 1;

    for (i = 1; i <= nb; i++) {
        result *= i;
    }

    return result;
}