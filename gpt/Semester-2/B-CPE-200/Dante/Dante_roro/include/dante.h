/*
** EPITECH PROJECT, 2025
** Dante Solver
** File description:
** Prototypes
*/

#ifndef DANTE_H
    #define DANTE_H

typedef struct {
    int w;
    int h;
    char *cells;
} maze_t;

maze_t *maze_from_string(const char *s);
void maze_destroy(maze_t *m);
char *solve_maze(const maze_t *m);
int read_file(const char *path, char **out);

#endif /* DANTE_H */

