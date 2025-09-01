/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Required functions for palindrome project
*/

#include <stdlib.h>

int my_factrec_synthesis(int nb)
{
    if (nb < 0)
        return 0;
    if (nb == 0 || nb == 1)
        return 1;
    
    if (nb > 12) // Prevent overflow for int (12! = 479001600)
        return 0;
    
    return nb * my_factrec_synthesis(nb - 1);
}

int my_squareroot_synthesis(int nb)
{
    int i;
    
    if (nb < 0)
        return -1;
    if (nb == 0)
        return 0;
    if (nb == 1)
        return 1;
    
    for (i = 1; i * i <= nb; i++) {
        if (i * i == nb)
            return i;
        if (i > 46340) // Prevent overflow (46340^2 = 2147395600)
            break;
    }
    
    return -1;
}