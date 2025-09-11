/*
** EPITECH PROJECT, 2024
** Day07 - B-CPE-100
** File description:
** my_is_prime.c
*/

int my_is_prime(int nb)
{
    int i = 2;
    
    if (nb < 2)
        return 0;
    
    while (i * i <= nb) {
        if (nb % i == 0)
            return 0;
        i++;
    }
    
    return 1;
}