/*
** EPITECH PROJECT, 2025
** My_sudo_roro
** File description:
** Prototypes for Sudoku solver
*/

#ifndef SUDOKU_H
    #define SUDOKU_H

    #define ERR_CODE 84

    typedef struct grid_s {
        char cells[9][9];
    } grid_t;

    int load_grid(const char *path, grid_t *g);
    int validate_grid(const grid_t *g);
    int solve_grid(grid_t *g);
    void print_grid(const grid_t *g);

#endif /* SUDOKU_H */
