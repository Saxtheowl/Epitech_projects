/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Map management functions for MyRunner project
*/

#include "my_runner.h"

int load_map(game_t *game, const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int y = 0;
    
    if (!file) {
        fprintf(stderr, "Error: Cannot open map file %s\n", filepath);
        return -1;
    }
    
    // Initialize map
    game->map.width = 0;
    game->map.height = 0;
    game->map.scroll_offset = 0;
    
    // Read map file
    while ((read = getline(&line, &len, file)) != -1 && y < MAX_MAP_HEIGHT) {
        int x = 0;
        for (int i = 0; line[i] && line[i] != '\n' && x < MAX_MAP_WIDTH; i++) {
            if (line[i] >= '0' && line[i] <= '9') {
                game->map.tiles[y][x].type = line[i] - '0';
                
                // Create tile sprite and texture
                game->map.tiles[y][x].texture = sfTexture_create(TILE_SIZE, TILE_SIZE);
                game->map.tiles[y][x].sprite = sfSprite_create();
                
                if (game->map.tiles[y][x].texture && game->map.tiles[y][x].sprite) {
                    sfSprite_setTexture(game->map.tiles[y][x].sprite, 
                                       game->map.tiles[y][x].texture, sfTrue);
                    
                    game->map.tiles[y][x].position.x = x * TILE_SIZE;
                    game->map.tiles[y][x].position.y = y * TILE_SIZE;
                    
                    sfSprite_setPosition(game->map.tiles[y][x].sprite, 
                                        game->map.tiles[y][x].position);
                }
                x++;
            } else if (line[i] == ' ') {
                game->map.tiles[y][x].type = 0; // Empty space
                game->map.tiles[y][x].sprite = NULL;
                game->map.tiles[y][x].texture = NULL;
                x++;
            }
        }
        if (x > game->map.width)
            game->map.width = x;
        y++;
    }
    
    game->map.height = y;
    
    free(line);
    fclose(file);
    
    if (game->map.width == 0 || game->map.height == 0) {
        fprintf(stderr, "Error: Invalid or empty map file\n");
        return -1;
    }
    
    return 0;
}

void update_map(game_t *game, float delta_time)
{
    // Scroll the map to the left
    game->map.scroll_offset += game->camera_speed * delta_time;
    
    // Update tile positions based on scroll offset
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            if (game->map.tiles[y][x].sprite) {
                sfVector2f pos = {
                    x * TILE_SIZE - game->map.scroll_offset,
                    y * TILE_SIZE
                };
                sfSprite_setPosition(game->map.tiles[y][x].sprite, pos);
            }
        }
    }
}

void draw_map(game_t *game)
{
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            if (game->map.tiles[y][x].sprite && game->map.tiles[y][x].type > 0) {
                // Only draw tiles that are visible on screen
                float tile_screen_x = x * TILE_SIZE - game->map.scroll_offset;
                if (tile_screen_x > -TILE_SIZE && tile_screen_x < WINDOW_WIDTH + TILE_SIZE) {
                    // Set different colors based on tile type
                    sfColor tile_color = sfWhite;
                    switch (game->map.tiles[y][x].type) {
                        case 1: tile_color = sfGreen; break;  // Ground
                        case 2: tile_color = sfRed; break;    // Spikes
                        case 3: tile_color = sfBlue; break;   // Special blocks
                        default: tile_color = sfWhite; break;
                    }
                    
                    // Create a colored rectangle for the tile
                    sfRectangleShape *tile_shape = sfRectangleShape_create();
                    sfVector2f size = {TILE_SIZE, TILE_SIZE};
                    sfRectangleShape_setSize(tile_shape, size);
                    sfRectangleShape_setFillColor(tile_shape, tile_color);
                    
                    sfVector2f pos = {tile_screen_x, y * TILE_SIZE};
                    sfRectangleShape_setPosition(tile_shape, pos);
                    
                    sfRenderWindow_drawRectangleShape(game->window, tile_shape, NULL);
                    sfRectangleShape_destroy(tile_shape);
                }
            }
        }
    }
}

int check_collision_with_map(game_t *game, sfVector2f pos)
{
    int tile_x = (int)(pos.x + game->map.scroll_offset) / TILE_SIZE;
    int tile_y = (int)pos.y / TILE_SIZE;
    
    return get_tile_type(game, tile_x, tile_y) > 0;
}

int get_tile_type(game_t *game, int x, int y)
{
    if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
        return 0;
    return game->map.tiles[y][x].type;
}