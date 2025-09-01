/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Argument parsing functions
*/

#include "palindrome.h"

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./palindrome -n number -p palindrome [-b base] [-imin i] [-imax i]\n");
    printf("DESCRIPTION\n");
    printf("    -n n        integer to be transformed (>=0)\n");
    printf("    -p pal      palindromic number to be obtained (incompatible with the -n\n");
    printf("                option) (>=0)\n");
    printf("                if defined, all fitting values of n will be output\n");
    printf("    -b base     base in which the procedure will be executed (1<b<=10) [def: 10]\n");
    printf("    -imin i     minimum number of iterations, included (>=0) [def: 0]\n");
    printf("    -imax i     maximum number of iterations, included (>=0) [def: 100]\n");
}

int parse_arguments(int ac, char **av, params_t *params)
{
    int i;
    int n_set = 0, p_set = 0;
    
    // Initialize default values
    params->base = 10;
    params->imin = 0;
    params->imax = 100;
    params->mode = -1;
    
    for (i = 1; i < ac; i++) {
        if (my_strlen(av[i]) >= 2 && av[i][0] == '-') {
            if (av[i][1] == 'n' && i + 1 < ac) {
                if (!is_valid_number(av[i + 1]) || my_atoi(av[i + 1]) < 0)
                    return 84;
                params->number = my_atoi(av[i + 1]);
                params->mode = 0;
                n_set = 1;
                i++;
            } else if (av[i][1] == 'p' && i + 1 < ac) {
                if (!is_valid_number(av[i + 1]) || my_atoi(av[i + 1]) < 0)
                    return 84;
                params->palindrome = my_atoi(av[i + 1]);
                params->mode = 1;
                p_set = 1;
                i++;
            } else if (av[i][1] == 'b' && i + 1 < ac) {
                if (!is_valid_number(av[i + 1]))
                    return 84;
                params->base = my_atoi(av[i + 1]);
                if (params->base <= 1 || params->base > 10)
                    return 84;
                i++;
            } else if (my_strlen(av[i]) >= 5 && av[i][1] == 'i' && av[i][2] == 'm' && 
                      av[i][3] == 'i' && av[i][4] == 'n' && i + 1 < ac) {
                if (!is_valid_number(av[i + 1]) || my_atoi(av[i + 1]) < 0)
                    return 84;
                params->imin = my_atoi(av[i + 1]);
                i++;
            } else if (my_strlen(av[i]) >= 5 && av[i][1] == 'i' && av[i][2] == 'm' && 
                      av[i][3] == 'a' && av[i][4] == 'x' && i + 1 < ac) {
                if (!is_valid_number(av[i + 1]) || my_atoi(av[i + 1]) < 0)
                    return 84;
                params->imax = my_atoi(av[i + 1]);
                i++;
            } else {
                return 84;
            }
        } else {
            return 84;
        }
    }
    
    if (n_set && p_set)
        return 84;
    if (!n_set && !p_set)
        return 84;
    if (params->imin > params->imax)
        return 84;
    
    return 0;
}