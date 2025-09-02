/*
** EPITECH PROJECT, 2025
** Game of Stones
** File description:
** Main entry point for Game of Stones
*/

#include "game_of_stones.h"

void display_help(void)
{
    printf("USAGE\n");
    printf("    ./game_of_stones [--links FR P1 P2 | --plots FR CR n]\n");
    printf("DESCRIPTION\n");
    printf("    FR    file containing friendship relations between people\n");
    printf("    Pi    name of someone in the friendships file\n");
    printf("    CR    file containing conspiracies intentions\n");
    printf("    n     maximum length of friendship paths\n");
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        display_help();
        return 0;
    }

    if (argc == 5 && strcmp(argv[1], "--links") == 0) {
        return links_mode(argv[2], argv[3], argv[4]);
    }

    if (argc == 5 && strcmp(argv[1], "--plots") == 0) {
        int n = atoi(argv[4]);
        if (n <= 0) {
            fprintf(stderr, "Error: n must be a positive integer\n");
            return 84;
        }
        return plots_mode(argv[2], argv[3], n);
    }

    display_help();
    return 84;
}