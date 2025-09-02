/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Argument parsing functions
*/

#include "groundhog.h"

int display_help(void)
{
    printf("SYNOPSIS\n");
    printf("    ./groundhog period\n");
    printf("DESCRIPTION\n");
    printf("    period    the number of days defining a period\n");
    return SUCCESS_EXIT;
}

int parse_arguments(int argc, char **argv)
{
    int period = 0;

    if (argc != 2) {
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }
    if (strcmp(argv[1], "-h") == 0) {
        display_help();
        exit(SUCCESS_EXIT);
    }
    period = atoi(argv[1]);
    if (period <= 0) {
        fprintf(stderr, "Invalid period value\n");
        return -1;
    }
    return period;
}