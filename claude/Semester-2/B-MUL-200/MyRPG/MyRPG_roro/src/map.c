/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Map system implementation
*/

#include "../include/my_rpg.h"

void init_map(game_t *game)
{
    game->map.width = MAP_WIDTH;
    game->map.height = MAP_HEIGHT;
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                game->map.tiles[y][x] = 1;
            } else if ((x % 5 == 0 && y % 5 == 0) && (random_int(0, 100) < 30)) {
                game->map.tiles[y][x] = 1;
            } else {
                game->map.tiles[y][x] = 0;
            }
        }
    }
    
    game->map.tiles[5][5] = 0;
    game->map.tiles[8][3] = 0;
    game->map.tiles[12][8] = 0;
    
    for (int i = 0; i < MAX_MAP_SPRITES; i++) {
        game->map.sprites[i] = sfSprite_create();
        if (game->map.sprites[i]) {
            if (i == 0 && game->textures[4]) {
                sfSprite_setTexture(game->map.sprites[i], game->textures[4], sfFalse);
            } else if (i == 1 && game->textures[5]) {
                sfSprite_setTexture(game->map.sprites[i], game->textures[5], sfFalse);
            }
        }
    }
}

void render_map(game_t *game)
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (game->map.sprites[game->map.tiles[y][x]]) {
                sfSprite_setPosition(game->map.sprites[game->map.tiles[y][x]], 
                    (sfVector2f){
                        x * TILE_SIZE - game->camera.x,
                        y * TILE_SIZE - game->camera.y
                    });
                
                sfRenderWindow_drawSprite(game->window, 
                    game->map.sprites[game->map.tiles[y][x]], NULL);
            }
        }
    }
}

int check_map_collision(game_t *game, vector2_t pos)
{
    int x = (int)pos.x;
    int y = (int)pos.y;
    
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 1;
    
    return game->map.tiles[y][x] == 1;
}