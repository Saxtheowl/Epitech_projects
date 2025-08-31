/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Navy file parser for ship positions
*/

#include "../include/my_navy.h"

static int parse_position_coords(char *pos, int *x, int *y)
{
    if (my_strlen(pos) != 2)
        return -1;
    if (pos[0] < 'A' || pos[0] > 'H')
        return -1;
    if (pos[1] < '1' || pos[1] > '8')
        return -1;
    *x = pos[0] - 'A';
    *y = pos[1] - '1';
    return 0;
}

static int parse_ship_line(char *line, ship_t *ship)
{
    char *length_str = line;
    char *first_pos = NULL;
    char *last_pos = NULL;
    int i = 0;

    while (line[i] && line[i] != ':')
        i++;
    if (line[i] != ':')
        return -1;
    line[i] = '\0';
    first_pos = &line[i + 1];
    i++;
    while (line[i] && line[i] != ':')
        i++;
    if (line[i] != ':')
        return -1;
    line[i] = '\0';
    last_pos = &line[i + 1];
    ship->length = 0;
    i = 0;
    while (length_str[i]) {
        if (length_str[i] < '0' || length_str[i] > '9')
            return -1;
        ship->length = ship->length * 10 + (length_str[i] - '0');
        i++;
    }
    if (parse_position_coords(first_pos, &ship->start_x, &ship->start_y) == -1)
        return -1;
    if (parse_position_coords(last_pos, &ship->end_x, &ship->end_y) == -1)
        return -1;
    ship->hits = 0;
    return 0;
}

int parse_navy_file(char *filename, game_t *game)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    int ship_count = 0;

    if (!file) {
        perror(filename);
        return -1;
    }
    while (getline(&line, &len, file) != -1 && ship_count < NB_SHIPS) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        if (parse_ship_line(line, &game->ships[ship_count]) == -1) {
            free(line);
            fclose(file);
            return -1;
        }
        ship_count++;
    }
    free(line);
    fclose(file);
    return ship_count == NB_SHIPS ? 0 : -1;
}