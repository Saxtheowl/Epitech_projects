/*
** EPITECH PROJECT, 2024
** Day02 - Bootcamp Phoenix
** File description:
** recursive_power.c
*/

int recursive_power(int nb, int p)
{
    if (p < 0)
        return 0;

    if (p == 0)
        return 1;

    return nb * recursive_power(nb, p - 1);
}