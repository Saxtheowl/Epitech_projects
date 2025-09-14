/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Utility functions for MyHunter project
*/

#include "my_hunter.h"

void display_help(void)
{
    printf("USAGE\n");
    printf("    ./my_hunter\n\n");
    printf("DESCRIPTION\n");
    printf("    MyHunter is a Duck Hunt-like game where you shoot ducks.\n\n");
    printf("    Controls:\n");
    printf("    - Click on ducks to shoot them\n");
    printf("    - ESC or close window to quit\n\n");
    printf("    Features:\n");
    printf("    - Animated duck sprites\n");
    printf("    - Score system\n");
    printf("    - Moving targets\n");
}

float get_random_float(float min, float max)
{
    float random = (float)rand() / (float)RAND_MAX;
    return min + random * (max - min);
}

int parse_arguments(int ac, char **av)
{
    if (ac == 2 && av[1] != NULL) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            display_help();
            return 1;
        }
        fprintf(stderr, "Error: Invalid argument\n");
        return -1;
    }
    if (ac != 1) {
        fprintf(stderr, "Error: Too many arguments\n");
        return -1;
    }
    return 0;
}