/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Game logic and management functions
*/

#include "sokoban.h"

game_t *init_game(const char *map_file)
{
    game_t *game;
    
    if (map_file == NULL)
        return NULL;
    
    game = malloc(sizeof(game_t));
    if (game == NULL)
        return NULL;
    
    game->map = load_map_from_file(map_file);
    if (game->map == NULL || validate_map(game->map) == 0) {
        if (game->map != NULL)
            free_map(game->map);
        free(game);
        return NULL;
    }
    
    game->game_state = MY_EXIT_SUCCESS;
    game->is_running = true;
    
    return game;
}

void free_game(game_t *game)
{
    if (game == NULL)
        return;
    
    if (game->map != NULL)
        free_map(game->map);
    free(game);
}

static int can_move_to(sokoban_map_t *map, int x, int y)
{
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return 0;
    
    char cell = map->grid[y][x];
    return (cell == EMPTY || cell == TARGET);
}

static int can_push_box(sokoban_map_t *map, int from_x, int from_y, int to_x, int to_y)
{
    if (to_x < 0 || to_x >= map->width || to_y < 0 || to_y >= map->height)
        return 0;
    
    char from_cell = map->grid[from_y][from_x];
    char to_cell = map->grid[to_y][to_x];
    
    return ((from_cell == BOX || from_cell == BOX_ON_TARGET) && 
            (to_cell == EMPTY || to_cell == TARGET));
}

int move_player(game_t *game, int dx, int dy)
{
    int new_x = game->map->player_pos.x + dx;
    int new_y = game->map->player_pos.y + dy;
    char current_cell, target_cell;
    
    if (new_x < 0 || new_x >= game->map->width || 
        new_y < 0 || new_y >= game->map->height)
        return 0;
    
    target_cell = game->map->grid[new_y][new_x];
    current_cell = game->map->grid[game->map->player_pos.y][game->map->player_pos.x];
    
    if (target_cell == WALL)
        return 0;
    
    if (target_cell == BOX || target_cell == BOX_ON_TARGET) {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        
        if (!can_push_box(game->map, new_x, new_y, box_new_x, box_new_y))
            return 0;
        
        // Move box
        char box_target_cell = game->map->grid[box_new_y][box_new_x];
        if (box_target_cell == TARGET)
            game->map->grid[box_new_y][box_new_x] = BOX_ON_TARGET;
        else
            game->map->grid[box_new_y][box_new_x] = BOX;
        
        // Update current box position
        if (target_cell == BOX_ON_TARGET)
            game->map->grid[new_y][new_x] = TARGET;
        else
            game->map->grid[new_y][new_x] = EMPTY;
    }
    
    // Move player
    if (current_cell == PLAYER_ON_TARGET)
        game->map->grid[game->map->player_pos.y][game->map->player_pos.x] = TARGET;
    else
        game->map->grid[game->map->player_pos.y][game->map->player_pos.x] = EMPTY;
    
    if (game->map->grid[new_y][new_x] == TARGET)
        game->map->grid[new_y][new_x] = PLAYER_ON_TARGET;
    else
        game->map->grid[new_y][new_x] = PLAYER;
    
    game->map->player_pos.x = new_x;
    game->map->player_pos.y = new_y;
    
    return 1;
}

int check_win_condition(sokoban_map_t *map)
{
    int boxes_on_targets = 0;
    
    if (map == NULL)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == BOX_ON_TARGET)
                boxes_on_targets++;
        }
    }
    
    return (boxes_on_targets == map->boxes_count);
}

static int box_can_move(sokoban_map_t *map, int x, int y)
{
    if (map->grid[y][x] != BOX && map->grid[y][x] != BOX_ON_TARGET)
        return 0;
    
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        
        if (can_move_to(map, new_x, new_y))
            return 1;
    }
    
    return 0;
}

int check_lose_condition(sokoban_map_t *map)
{
    if (map == NULL)
        return 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->grid[y][x] == BOX || map->grid[y][x] == BOX_ON_TARGET) {
                if (box_can_move(map, x, y))
                    return 0;
            }
        }
    }
    
    return 1;
}

void reset_game(game_t *game, const char *map_file)
{
    sokoban_map_t *new_map;
    
    if (game == NULL || map_file == NULL)
        return;
    
    new_map = load_map_from_file(map_file);
    if (new_map == NULL || validate_map(new_map) == 0) {
        if (new_map != NULL)
            free_map(new_map);
        return;
    }
    
    free_map(game->map);
    game->map = new_map;
    game->game_state = MY_EXIT_SUCCESS;
    game->is_running = true;
}