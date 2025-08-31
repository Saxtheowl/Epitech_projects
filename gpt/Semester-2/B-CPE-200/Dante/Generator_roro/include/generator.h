/*
** EPITECH PROJECT, 2025
** Dante Generator
** File description:
** Prototypes
*/

#ifndef DANTE_GENERATOR_H
    #define DANTE_GENERATOR_H

typedef struct {
    int x;
    int y;
} cell_t;

int parse_args(int argc, char **argv, int *w, int *h, int *perfect);
char *generate_maze(int w, int h, int perfect);

#endif /* DANTE_GENERATOR_H */

