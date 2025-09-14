#include "my_navy.h"

int validate_ship_placement(ship_t *ship)
{
    if (ship->start_x < 0 || ship->start_x >= GRID_SIZE ||
        ship->start_y < 0 || ship->start_y >= GRID_SIZE ||
        ship->end_x < 0 || ship->end_x >= GRID_SIZE ||
        ship->end_y < 0 || ship->end_y >= GRID_SIZE)
        return 0;
    
    int dx = ship->end_x - ship->start_x;
    int dy = ship->end_y - ship->start_y;
    
    if (dx == 0 && dy == 0)
        return 0;
    
    if (dx != 0 && dy != 0)
        return 0;
    
    int actual_length;
    if (dx == 0)
        actual_length = (dy > 0) ? dy + 1 : -dy + 1;
    else
        actual_length = (dx > 0) ? dx + 1 : -dx + 1;
    
    return (actual_length == ship->length);
}

int parse_ship_line(char *line, ship_t *ship)
{
    int i = 0;
    int length = 0;
    
    if (!line || line[0] == '\n' || line[0] == '\0')
        return 0;
    
    while (line[i] && line[i] >= '0' && line[i] <= '9') {
        length = length * 10 + (line[i] - '0');
        i++;
    }
    
    if (line[i] != ':' || length < 2 || length > 5)
        return 0;
    
    ship->length = length;
    i++;
    
    if (line[i] < 'A' || line[i] > 'H' || line[i + 1] < '1' || line[i + 1] > '8')
        return 0;
    
    ship->start_y = line[i] - 'A';
    ship->start_x = line[i + 1] - '1';
    i += 2;
    
    if (line[i] != ':')
        return 0;
    i++;
    
    if (line[i] < 'A' || line[i] > 'H' || line[i + 1] < '1' || line[i + 1] > '8')
        return 0;
    
    ship->end_y = line[i] - 'A';
    ship->end_x = line[i + 1] - '1';
    
    ship->hits = 0;
    
    return validate_ship_placement(ship);
}

int check_ships_overlap(void)
{
    int i, j, k;
    
    for (i = 0; i < g_game.ship_count; i++) {
        for (j = i + 1; j < g_game.ship_count; j++) {
            ship_t *ship1 = &g_game.ships[i];
            ship_t *ship2 = &g_game.ships[j];
            
            int dx1 = ship1->end_x - ship1->start_x;
            int dy1 = ship1->end_y - ship1->start_y;
            int dx2 = ship2->end_x - ship2->start_x;
            int dy2 = ship2->end_y - ship2->start_y;
            
            if (dx1 < 0) dx1 = -dx1;
            if (dy1 < 0) dy1 = -dy1;
            if (dx2 < 0) dx2 = -dx2;
            if (dy2 < 0) dy2 = -dy2;
            
            for (k = 0; k <= dx1 + dy1; k++) {
                int x1 = ship1->start_x + (k * (ship1->end_x > ship1->start_x ? 1 : (ship1->end_x < ship1->start_x ? -1 : 0)));
                int y1 = ship1->start_y + (k * (ship1->end_y > ship1->start_y ? 1 : (ship1->end_y < ship1->start_y ? -1 : 0)));
                
                int l;
                for (l = 0; l <= dx2 + dy2; l++) {
                    int x2 = ship2->start_x + (l * (ship2->end_x > ship2->start_x ? 1 : (ship2->end_x < ship2->start_x ? -1 : 0)));
                    int y2 = ship2->start_y + (l * (ship2->end_y > ship2->start_y ? 1 : (ship2->end_y < ship2->start_y ? -1 : 0)));
                    
                    if (x1 == x2 && y1 == y2)
                        return 1;
                }
            }
        }
    }
    return 0;
}

int parse_positions_file(char const *filename)
{
    FILE *file = fopen(filename, "r");
    char buffer[BUFFER_SIZE];
    int expected_lengths[MAX_SHIPS] = {2, 3, 4, 5};
    int found_lengths[MAX_SHIPS] = {0, 0, 0, 0};
    
    if (!file)
        return 84;
    
    g_game.ship_count = 0;
    
    while (fgets(buffer, BUFFER_SIZE, file) && g_game.ship_count < MAX_SHIPS) {
        if (buffer[0] == '\n' || buffer[0] == '\0')
            continue;
            
        if (parse_ship_line(buffer, &g_game.ships[g_game.ship_count])) {
            int i;
            for (i = 0; i < MAX_SHIPS; i++) {
                if (expected_lengths[i] == g_game.ships[g_game.ship_count].length) {
                    found_lengths[i]++;
                    break;
                }
            }
            g_game.ship_count++;
        } else {
            fclose(file);
            return 84;
        }
    }
    
    fclose(file);
    
    if (g_game.ship_count != MAX_SHIPS)
        return 84;
    
    int i;
    for (i = 0; i < MAX_SHIPS; i++) {
        if (found_lengths[i] != 1)
            return 84;
    }
    
    if (check_ships_overlap())
        return 84;
    
    return 0;
}