/*
** EPITECH PROJECT, 2024
** Matchstick
** File description:
** Utility functions
*/

#include "../include/matchstick.h"

int my_atoi(const char *str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (!str)
        return 0;
        
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
        
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

void print_error(const char *message)
{
    write(2, message, strlen(message));
    write(2, "\n", 1);
}

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./matchstick lines max_matches_per_turn\n");
    printf("DESCRIPTION\n");
    printf("    lines    number of lines (must be > 1 and < 100)\n");
    printf("    max_matches_per_turn    maximum number of matches you can take per turn (must be > 0)\n");
}

int check_arguments(int argc, char **argv)
{
    if (argc != 3) {
        print_usage();
        return -1;
    }
    
    if (my_atoi(argv[1]) <= 1 || my_atoi(argv[1]) >= 100) {
        print_error("Invalid number of lines");
        return -1;
    }
    
    if (my_atoi(argv[2]) <= 0) {
        print_error("Invalid max matches per turn");
        return -1;
    }
    
    return 0;
}