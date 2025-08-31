/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** Argument parsing for my_sokoban
*/

#include "../include/my_sokoban.h"

void print_usage(void)
{
    printf("USAGE\n");
    printf("    ./my_sokoban map\n");
    printf("DESCRIPTION\n");
    printf("    map file representing the warehouse map, containing '#' ");
    printf("for walls,\n");
    printf("    'P' for the player, 'X' for boxes and 'O' for storage ");
    printf("locations.\n");
}

int parse_arguments(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_usage();
        exit(0);
    }
    if (argc != 2) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return -1;
    }
    return 0;
}