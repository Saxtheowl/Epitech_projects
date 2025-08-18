#include "my_sokoban.h"

int move_player(map_t *map, int dx, int dy)
{
    int new_x = map->player.x + dx;
    int new_y = map->player.y + dy;
    
    if (new_x < 0 || new_x >= map->width || new_y < 0 || new_y >= map->height)
        return -1;
    
    char target = map->grid[new_y][new_x];
    
    if (target == WALL)
        return -1;
    
    if (target == BOX) {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        
        if (box_new_x < 0 || box_new_x >= map->width || 
            box_new_y < 0 || box_new_y >= map->height)
            return -1;
        
        char box_target = map->grid[box_new_y][box_new_x];
        
        if (box_target == WALL || box_target == BOX)
            return -1;
        
        map->grid[box_new_y][box_new_x] = BOX;
        map->grid[new_y][new_x] = PLAYER;
    } else {
        map->grid[new_y][new_x] = PLAYER;
    }
    
    if (map->original[map->player.y][map->player.x] == STORAGE) {
        map->grid[map->player.y][map->player.x] = STORAGE;
    } else {
        map->grid[map->player.y][map->player.x] = SPACE;
    }
    
    map->player.x = new_x;
    map->player.y = new_y;
    
    return 0;
}

int check_win(map_t *map)
{
    if (!map || !map->grid)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->original[y][x] == STORAGE && map->grid[y][x] != BOX) {
                return 0;
            }
        }
    }
    
    return 1;
}

int can_box_move(map_t *map, int x, int y)
{
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        
        if (new_x >= 0 && new_x < map->width && new_y >= 0 && new_y < map->height) {
            if (map->grid[new_y][new_x] == SPACE || 
                (map->grid[new_y][new_x] == STORAGE && map->original[new_y][new_x] == STORAGE)) {
                
                int player_x = x - directions[i][0];
                int player_y = y - directions[i][1];
                
                if (player_x >= 0 && player_x < map->width && 
                    player_y >= 0 && player_y < map->height) {
                    if (map->grid[player_y][player_x] == SPACE || 
                        map->grid[player_y][player_x] == PLAYER ||
                        (map->grid[player_y][player_x] == STORAGE && map->original[player_y][player_x] == STORAGE)) {
                        return 1;
                    }
                }
            }
        }
    }
    
    return 0;
}

int check_lose(map_t *map)
{
    if (!map || !map->grid)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == BOX) {
                if (can_box_move(map, x, y)) {
                    return 0;
                }
            }
        }
    }
    
    return 1;
}

void reset_game(map_t *map)
{
    if (!map || !map->grid || !map->original)
        return;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            map->grid[y][x] = map->original[y][x];
        }
    }
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == PLAYER) {
                map->player.x = x;
                map->player.y = y;
                return;
            }
        }
    }
}

void game_loop(map_t *map)
{
    int key;
    int game_over = 0;
    
    while (!game_over) {
        if (check_terminal_size(map) == 0) {
            display_map(map);
            
            if (check_win(map)) {
                display_message("You win! Press any key to exit.");
                getchar();
                game_over = 1;
                continue;
            }
            
            if (check_lose(map)) {
                display_message("You lose! Press SPACE to restart or q to exit.");
                key = getchar();
                if (key == ' ') {
                    reset_game(map);
                    continue;
                } else {
                    game_over = 1;
                    continue;
                }
            }
        }
        
        printf("Enter move (w/a/s/d/space/q): ");
        key = getchar();
        if (key == '\n') key = getchar();
        
        switch (key) {
            case 'w':
            case 'W':
                if (check_terminal_size(map) == 0)
                    move_player(map, 0, -1);
                break;
            case 's':
            case 'S':
                if (check_terminal_size(map) == 0)
                    move_player(map, 0, 1);
                break;
            case 'a':
            case 'A':
                if (check_terminal_size(map) == 0)
                    move_player(map, -1, 0);
                break;
            case 'd':
            case 'D':
                if (check_terminal_size(map) == 0)
                    move_player(map, 1, 0);
                break;
            case ' ':
                reset_game(map);
                break;
            case 'q':
            case 'Q':
                game_over = 1;
                break;
        }
    }
}