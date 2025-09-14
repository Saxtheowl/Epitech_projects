#include "palindrome.h"

long long reverse_number(long long num, int base)
{
    long long reversed = 0;
    
    while (num > 0) {
        reversed = reversed * base + (num % base);
        num /= base;
    }
    return reversed;
}

int is_palindrome(long long num, int base)
{
    return num == reverse_number(num, base);
}

long long add_numbers(long long num1, long long num2)
{
    return num1 + num2;
}

int find_palindrome_iterations(int n, int base, int max_iter)
{
    long long current = n;
    int iterations = 0;
    
    while (iterations <= max_iter) {
        if (is_palindrome(current, base))
            return iterations;
        
        long long reversed = reverse_number(current, base);
        current = add_numbers(current, reversed);
        iterations++;
        
        // Prevent overflow
        if (current < 0 || current > 1000000000)
            return -1;
    }
    
    return -1;
}

int find_iterations_to_target(int n, int target, int base, int max_iter)
{
    long long current = n;
    int iterations = 0;
    
    while (iterations <= max_iter) {
        if (current == target)
            return iterations;
        
        long long reversed = reverse_number(current, base);
        current = add_numbers(current, reversed);
        iterations++;
        
        // Prevent overflow
        if (current < 0 || current > 1000000000)
            return -1;
    }
    
    return -1;
}

void process_n_mode(config_t *config)
{
    int iterations = find_palindrome_iterations(config->n, config->base, config->imax);
    
    if (iterations == -1 || iterations < config->imin) {
        printf("no solution\n");
        return;
    }
    
    // Find the palindrome result
    long long current = config->n;
    int i;
    
    for (i = 0; i < iterations; i++) {
        long long reversed = reverse_number(current, config->base);
        current = add_numbers(current, reversed);
    }
    
    printf("%d leads to %lld in %d iteration(s) in base %d\n", 
           config->n, current, iterations, config->base);
}

void process_p_mode(config_t *config)
{
    int found = 0;
    int n;
    
    // Search through possible values of n with a reasonable upper bound
    for (n = 0; n <= 10000; n++) {
        int iterations = find_iterations_to_target(n, config->p, config->base, config->imax);
        
        if (iterations != -1 && iterations >= config->imin && iterations <= config->imax) {
            printf("%d leads to %d in %d iteration(s) in base %d\n", 
                   n, config->p, iterations, config->base);
            found = 1;
        }
    }
    
    if (!found) {
        printf("no solution\n");
    }
}