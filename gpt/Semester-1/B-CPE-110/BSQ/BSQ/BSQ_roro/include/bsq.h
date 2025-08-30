/*
** EPITECH PROJECT, 2025
** BSQ_roro
** File description:
** Prototypes for BSQ
*/

#ifndef BSQ_H
    #define BSQ_H

    #define ERR_CODE 84

    typedef struct map_s {
        char **grid;
        int rows;
        int cols;
    } map_t;

    int load_map(const char *path, map_t *map);
    int validate_map(map_t *map);
    void free_map(map_t *map);
    void print_map(const map_t *map);

    int solve_bsq(map_t *map);

#endif /* BSQ_H */
