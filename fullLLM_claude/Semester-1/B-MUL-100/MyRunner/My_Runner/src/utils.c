/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Utility functions for MyRunner project
*/

#include "my_runner.h"

void display_help(void)
{
    printf("Finite runner created with CSFML.\n");
    printf("USAGE\n");
    printf("    ./my_runner map.txt\n\n");
    printf("OPTIONS\n");
    printf("    -i    launch the game in infinity mode.\n");
    printf("    -h    print the usage and quit.\n\n");
    printf("USER INTERACTIONS\n");
    printf("    SPACE_KEY    jump.\n");
}

int parse_arguments(int ac, char **av, char **map_path, int *infinity_mode)
{
    if (ac == 1) {
        fprintf(stderr, "./my_runner: bad arguments: 0 given but 1 is required\n");
        fprintf(stderr, "retry with -h\n");
        return -1;
    }

    if (ac == 2 && av[1] != NULL) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            display_help();
            return 1;
        }
        if (av[1][0] == '-' && av[1][1] == 'i' && av[1][2] == '\0') {
            *infinity_mode = 1;
            return 0;
        }
        *map_path = av[1];
        return 0;
    }

    if (ac == 3 && av[1] != NULL && av[2] != NULL) {
        if (av[1][0] == '-' && av[1][1] == 'i' && av[1][2] == '\0') {
            *infinity_mode = 1;
            *map_path = av[2];
            return 0;
        }
        if (av[2][0] == '-' && av[2][1] == 'i' && av[2][2] == '\0') {
            *infinity_mode = 1;
            *map_path = av[1];
            return 0;
        }
    }

    fprintf(stderr, "Error: Invalid arguments\n");
    return -1;
}

float get_random_float(float min, float max)
{
    float random = (float)rand() / (float)RAND_MAX;
    return min + random * (max - min);
}