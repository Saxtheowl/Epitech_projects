#include "sokoban.h"

int is_valid_map(sokoban_map_t *map)
{
    int i, j;
    int player_count = 0;
    
    if (!map || !map->map)
        return 0;
    
    if (map->player_pos.x == -1 || map->player_pos.y == -1)
        return 0;
    
    if (map->boxes_count == 0 || map->storage_count == 0)
        return 0;
    
    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            char c = map->map[i][j];
            if (c != WALL && c != PLAYER && c != BOX && c != STORAGE && c != EMPTY)
                return 0;
            if (c == PLAYER)
                player_count++;
        }
    }
    
    return player_count == 1;
}

int check_win_condition(sokoban_map_t *map)
{
    int i, j;
    int boxes_on_storage = 0;
    
    if (!map || !map->map)
        return 0;
    
    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (map->map[i][j] == BOX_ON_STORAGE)
                boxes_on_storage++;
        }
    }
    
    return boxes_on_storage == map->boxes_count;
}

static int can_box_move(sokoban_map_t *map, int x, int y, int dx, int dy)
{
    int new_x = x + dx;
    int new_y = y + dy;
    
    if (new_x < 0 || new_x >= map->width || new_y < 0 || new_y >= map->height)
        return 0;
    
    char dest = map->map[new_y][new_x];
    return (dest == EMPTY || dest == STORAGE);
}

int check_lose_condition(sokoban_map_t *map)
{
    int i, j;
    
    if (!map || !map->map)
        return 1;
    
    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            if (map->map[i][j] == BOX) {
                if (can_box_move(map, j, i, 0, 1) ||
                    can_box_move(map, j, i, 0, -1) ||
                    can_box_move(map, j, i, 1, 0) ||
                    can_box_move(map, j, i, -1, 0))
                    return 0;
            }
        }
    }
    
    return 1;
}

int can_move_box(sokoban_map_t *map, int x, int y, int dx, int dy)
{
    return can_box_move(map, x, y, dx, dy);
}

int move_player(sokoban_map_t *map, int dx, int dy)
{
    int new_x = map->player_pos.x + dx;
    int new_y = map->player_pos.y + dy;
    
    if (new_x < 0 || new_x >= map->width || new_y < 0 || new_y >= map->height)
        return 0;
    
    char dest = map->map[new_y][new_x];
    
    if (dest == WALL)
        return 0;
    
    if (dest == BOX || dest == BOX_ON_STORAGE) {
        if (!can_move_box(map, new_x, new_y, dx, dy))
            return 0;
        
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        char box_dest = map->map[box_new_y][box_new_x];
        
        if (box_dest == STORAGE)
            map->map[box_new_y][box_new_x] = BOX_ON_STORAGE;
        else
            map->map[box_new_y][box_new_x] = BOX;
        
        if (dest == BOX_ON_STORAGE)
            map->map[new_y][new_x] = STORAGE;
        else
            map->map[new_y][new_x] = EMPTY;
    }
    
    char old_pos = map->map[map->player_pos.y][map->player_pos.x];
    if (old_pos == PLAYER_ON_STORAGE)
        map->map[map->player_pos.y][map->player_pos.x] = STORAGE;
    else
        map->map[map->player_pos.y][map->player_pos.x] = EMPTY;
    
    if (dest == STORAGE || dest == BOX_ON_STORAGE)
        map->map[new_y][new_x] = PLAYER_ON_STORAGE;
    else
        map->map[new_y][new_x] = PLAYER;
    
    map->player_pos.x = new_x;
    map->player_pos.y = new_y;
    
    return 1;
}