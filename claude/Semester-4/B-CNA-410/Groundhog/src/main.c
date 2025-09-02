/*
** EPITECH PROJECT, 2025
** Groundhog
** File description:
** Main file for Groundhog weather analysis
*/

#include "groundhog.h"

void display_help(void)
{
    printf("SYNOPSIS\n");
    printf("    ./groundhog period\n");
    printf("DESCRIPTION\n");
    printf("    period    the number of days defining a period\n");
}

int main(int argc, char **argv)
{
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        display_help();
        return 0;
    }
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s period\n", argv[0]);
        return 84;
    }
    
    int period = atoi(argv[1]);
    if (period <= 0) {
        fprintf(stderr, "Error: period must be a positive integer\n");
        return 84;
    }
    
    return groundhog_main(period);
}