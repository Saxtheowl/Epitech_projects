/*
** EPITECH PROJECT, 2025
** Dante Generator
** File description:
** Entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator.h"

int parse_args(int argc, char **argv, int *w, int *h, int *perfect)
{
    long W; long H;
    char *end;

    if (argc < 3)
        return 0;
    W = strtol(argv[1], &end, 10);
    if (*end != '\0' || W <= 0 || W > 5000)
        return 0;
    H = strtol(argv[2], &end, 10);
    if (*end != '\0' || H <= 0 || H > 5000)
        return 0;
    *w = (int)W; *h = (int)H; *perfect = 0;
    if (argc >= 4 && argv[3] && argv[3][0] == 'p')
        *perfect = 1;
    return 1;
}

int main(int argc, char **argv)
{
    int w; int h; int perf;
    char *maze;

    if (!parse_args(argc, argv, &w, &h, &perf))
        return 84;
    srand((unsigned int)time(NULL));
    maze = generate_maze(w, h, perf);
    if (!maze)
        return 84;
    printf("%s\n", maze);
    free(maze);
    return 0;
}

