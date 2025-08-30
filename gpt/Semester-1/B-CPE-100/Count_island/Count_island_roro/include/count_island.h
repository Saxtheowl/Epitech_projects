/*
** EPITECH PROJECT, 2025
** Count_island_roro
** File description:
** Prototypes for count_island project
*/

#ifndef COUNT_ISLAND_H
    #define COUNT_ISLAND_H

    #include <stddef.h>

    #define ERR_CODE 84

    typedef struct map_s {
        char **grid;
        int rows;
        int cols;
    } map_t;

    int load_map(const char *path, map_t *map);
    void free_map(map_t *map);
    int validate_map(map_t *map);

    void print_map(const map_t *map);

    int label_islands(map_t *map);

    char label_for(int index);

#endif /* COUNT_ISLAND_H */

