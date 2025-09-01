/*
** EPITECH PROJECT, 2025
** Palindrome
** File description:
** Main function for palindrome project
*/

#include "palindrome.h"

int main(int ac, char **av)
{
    params_t params = {0};
    
    if (ac == 2 && my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        print_usage();
        return 0;
    }
    
    if (parse_arguments(ac, av, &params) == 84) {
        write(2, "invalid argument\n", 17);
        return 84;
    }
    
    if (params.mode == 0) {
        process_number_mode(&params);
    } else {
        process_palindrome_mode(&params);
    }
    
    return 0;
}