/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Palindrome algorithm implementation
*/

#include "palindrome.h"

int is_palindrome(long number, int base)
{
    return number == reverse_number(number, base);
}

long reverse_number(long number, int base)
{
    long result = 0;
    
    while (number > 0) {
        result = result * base + (number % base);
        number /= base;
    }
    
    return result;
}

int find_palindrome(long number, int base, int max_iterations)
{
    long current = number;
    int iterations = 0;
    
    while (iterations <= max_iterations) {
        if (is_palindrome(current, base))
            return iterations;
        
        current = current + reverse_number(current, base);
        iterations++;
    }
    
    return -1; // No palindrome found within max_iterations
}

void process_number_mode(params_t *params)
{
    int iterations = find_palindrome(params->number, params->base, params->imax);
    
    if (iterations == -1 || iterations < params->imin) {
        printf("no solution\n");
        return;
    }
    
    // Calculate the palindrome result
    long current = params->number;
    for (int i = 0; i < iterations; i++) {
        current = current + reverse_number(current, params->base);
    }
    
    printf("%d leads to %ld in %d iteration(s) in base %d\n",
           params->number, current, iterations, params->base);
}

void process_palindrome_mode(params_t *params)
{
    int found = 0;
    
    // Search through possible starting numbers
    for (long n = 0; n <= 100000; n++) {
        int iterations = find_palindrome(n, params->base, params->imax);
        
        if (iterations != -1 && iterations >= params->imin && iterations <= params->imax) {
            // Calculate the result palindrome
            long current = n;
            for (int i = 0; i < iterations; i++) {
                current = current + reverse_number(current, params->base);
            }
            
            if (current == params->palindrome) {
                printf("%ld leads to %d in %d iteration(s) in base %d\n",
                       n, params->palindrome, iterations, params->base);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("no solution\n");
    }
}