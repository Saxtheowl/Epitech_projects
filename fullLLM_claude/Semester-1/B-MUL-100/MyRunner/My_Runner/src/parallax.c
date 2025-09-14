/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Parallax background system for MyRunner project
*/

#include "my_runner.h"

int init_parallax(game_t *game)
{
    for (int i = 0; i < PARALLAX_LAYERS; i++) {
        // Create textures for each parallax layer
        game->parallax[i].texture = sfTexture_create(WINDOW_WIDTH, WINDOW_HEIGHT);
        if (!game->parallax[i].texture)
            return -1;
            
        // Create sprites
        game->parallax[i].sprite = sfSprite_create();
        if (!game->parallax[i].sprite)
            return -1;
            
        sfSprite_setTexture(game->parallax[i].sprite, game->parallax[i].texture, sfTrue);
        
        // Set different speeds for each layer (further layers move slower)
        game->parallax[i].speed = (i + 1) * 0.3f;
        game->parallax[i].offset = 0;
        
        // Set different colors for visual distinction
        sfColor layer_colors[] = {
            {30, 30, 60, 255},    // Dark blue (far background)
            {60, 60, 100, 255},   // Medium blue
            {100, 100, 150, 255}  // Light blue (near background)
        };
        
        // Create a colored rectangle for the layer
        sfRectangleShape *layer_rect = sfRectangleShape_create();
        sfVector2f size = {WINDOW_WIDTH, WINDOW_HEIGHT};
        sfRectangleShape_setSize(layer_rect, size);
        sfRectangleShape_setFillColor(layer_rect, layer_colors[i]);
        
        // For now, we'll just use solid colors as parallax layers
        // In a real game, you'd load background images here
    }
    
    return 0;
}

void update_parallax(game_t *game, float delta_time)
{
    for (int i = 0; i < PARALLAX_LAYERS; i++) {
        // Update offset based on camera speed and layer speed
        game->parallax[i].offset += game->camera_speed * game->parallax[i].speed * delta_time;
        
        // Wrap around when offset exceeds window width
        if (game->parallax[i].offset >= WINDOW_WIDTH)
            game->parallax[i].offset -= WINDOW_WIDTH;
    }
}

void draw_parallax(game_t *game)
{
    // Draw each parallax layer
    for (int i = 0; i < PARALLAX_LAYERS; i++) {
        // Set different colors for visual distinction
        sfColor layer_colors[] = {
            {20, 20, 40, 255},    // Dark blue (far background)
            {40, 40, 70, 255},    // Medium blue
            {70, 70, 120, 255}    // Light blue (near background)
        };
        
        // Draw two rectangles side by side to create seamless scrolling
        for (int j = 0; j < 2; j++) {
            sfRectangleShape *layer_rect = sfRectangleShape_create();
            sfVector2f size = {WINDOW_WIDTH, WINDOW_HEIGHT};
            sfRectangleShape_setSize(layer_rect, size);
            sfRectangleShape_setFillColor(layer_rect, layer_colors[i]);
            
            sfVector2f pos = {
                j * WINDOW_WIDTH - game->parallax[i].offset,
                0
            };
            sfRectangleShape_setPosition(layer_rect, pos);
            
            sfRenderWindow_drawRectangleShape(game->window, layer_rect, NULL);
            sfRectangleShape_destroy(layer_rect);
        }
    }
}