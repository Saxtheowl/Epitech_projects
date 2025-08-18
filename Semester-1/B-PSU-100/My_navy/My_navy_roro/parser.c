#include "my_navy.h"

int char_to_x(char c)
{
    if (c >= 'A' && c <= 'H')
        return c - 'A';
    return -1;
}

int char_to_y(char c)
{
    if (c >= '1' && c <= '8')
        return c - '1';
    return -1;
}

char x_to_char(int x)
{
    if (x >= 0 && x < GRID_SIZE)
        return 'A' + x;
    return '?';
}

char y_to_char(int y)
{
    if (y >= 0 && y < GRID_SIZE)
        return '1' + y;
    return '?';
}

int parse_position(char *pos, int *x, int *y)
{
    if (!pos || my_strlen(pos) != 2)
        return -1;
    
    *x = char_to_x(pos[0]);
    *y = char_to_y(pos[1]);
    
    if (*x == -1 || *y == -1)
        return -1;
    
    return 0;
}

int validate_ship_placement(ship_t *ship)
{
    int dx = ship->end_x - ship->start_x;
    int dy = ship->end_y - ship->start_y;
    int actual_length;
    
    if (dx != 0 && dy != 0)
        return -1;
    
    if (dx == 0)
        actual_length = (dy > 0) ? dy + 1 : -dy + 1;
    else
        actual_length = (dx > 0) ? dx + 1 : -dx + 1;
    
    if (actual_length != ship->length)
        return -1;
    
    return 0;
}

void place_ship(ship_t *ship)
{
    int x, y;
    int dx = (ship->end_x > ship->start_x) ? 1 : (ship->end_x < ship->start_x) ? -1 : 0;
    int dy = (ship->end_y > ship->start_y) ? 1 : (ship->end_y < ship->start_y) ? -1 : 0;
    
    x = ship->start_x;
    y = ship->start_y;
    
    for (int i = 0; i < ship->length; i++) {
        g_game.my_grid[y][x] = '0' + ship->length;
        x += dx;
        y += dy;
    }
}

int parse_ship_line(char *line, ship_t *ship)
{
    char *token;
    char *start_pos, *end_pos;
    char *saveptr;
    
    token = strtok_r(line, ":", &saveptr);
    if (!token)
        return -1;
    ship->length = my_atoi(token);
    
    token = strtok_r(NULL, ":", &saveptr);
    if (!token)
        return -1;
    start_pos = token;
    
    token = strtok_r(NULL, ":", &saveptr);
    if (!token)
        return -1;
    end_pos = token;
    
    if (parse_position(start_pos, &ship->start_x, &ship->start_y) != 0)
        return -1;
    if (parse_position(end_pos, &ship->end_x, &ship->end_y) != 0)
        return -1;
    
    return validate_ship_placement(ship);
}

int parse_positions_file(char *filename)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    int ship_count = 0;
    int expected_lengths[] = {2, 3, 4, 5};
    int found_lengths[] = {0, 0, 0, 0};
    
    file = fopen(filename, "r");
    if (!file)
        return -1;
    
    while (getline(&line, &len, file) != -1 && ship_count < SHIP_COUNT) {
        if (line[my_strlen(line) - 1] == '\n')
            line[my_strlen(line) - 1] = '\0';
        
        if (parse_ship_line(line, &g_game.ships[ship_count]) != 0) {
            free(line);
            fclose(file);
            return -1;
        }
        
        ship_count++;
    }
    
    free(line);
    fclose(file);
    
    if (ship_count != SHIP_COUNT)
        return -1;
    
    for (int i = 0; i < SHIP_COUNT; i++) {
        for (int j = 0; j < SHIP_COUNT; j++) {
            if (g_game.ships[i].length == expected_lengths[j]) {
                found_lengths[j]++;
                break;
            }
        }
    }
    
    for (int i = 0; i < SHIP_COUNT; i++) {
        if (found_lengths[i] != 1)
            return -1;
    }
    
    for (int i = 0; i < SHIP_COUNT; i++) {
        place_ship(&g_game.ships[i]);
    }
    
    return 0;
}