/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Utility functions for MyRadar project
*/

#include "my_radar.h"

void display_help(void)
{
    printf("Air traffic simulation panel\n");
    printf("USAGE\n");
    printf("    ./my_radar [OPTIONS] path_to_script\n");
    printf("    path_to_script    The path to the script file.\n\n");
    printf("OPTIONS\n");
    printf("    -h    print the usage and quit.\n\n");
    printf("USER INTERACTIONS\n");
    printf("    `L' key    enable/disable hitboxes and areas.\n");
    printf("    `S' key    enable/disable sprites.\n");
}

int parse_arguments(int ac, char **av, char **script_path)
{
    if (ac == 2 && av[1] != NULL) {
        if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
            display_help();
            return 1;
        }
        *script_path = av[1];
        return 0;
    }
    if (ac == 1) {
        fprintf(stderr, "./my_radar: bad arguments: 0 given but 84 is required\n");
        fprintf(stderr, "retry with -h\n");
        return -1;
    }
    fprintf(stderr, "Error: Invalid arguments\n");
    return -1;
}

float distance(sfVector2f a, sfVector2f b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

sfVector2f normalize_vector(sfVector2f vec)
{
    float length = sqrt(vec.x * vec.x + vec.y * vec.y);
    sfVector2f normalized = {0, 0};
    
    if (length > 0) {
        normalized.x = vec.x / length;
        normalized.y = vec.y / length;
    }
    return normalized;
}