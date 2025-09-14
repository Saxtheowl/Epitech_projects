/*
** EPITECH PROJECT, 2024
** Primes Generator
** File description:
** Generate prime numbers between two given numbers
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int my_sqrt(int n)
{
    int i = 1;
    
    while (i * i <= n)
        i++;
    return i - 1;
}

int is_prime(int n)
{
    int i;
    int sqrt_n;
    
    if (n < 2)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    
    sqrt_n = my_sqrt(n);
    for (i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0)
            return 0;
    }
    
    return 1;
}

int main(int argc, char **argv)
{
    int start, end, i, temp;
    
    if (argc != 3) {
        return 84;
    }
    
    start = atoi(argv[1]);
    end = atoi(argv[2]);
    
    if (start > end) {
        temp = start;
        start = end;
        end = temp;
    }
    
    for (i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
    
    return 0;
}