/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Camera system implementation
*/

#include "../include/my_rpg.h"

void init_camera(game_t *game)
{
    game->camera.x = 0.0f;
    game->camera.y = 0.0f;
    game->camera.zoom = 1.0f;
    game->camera.rotation = 0.0f;
    game->camera.target_x = 0.0f;
    game->camera.target_y = 0.0f;
    game->camera.target_zoom = 1.0f;
    game->camera.target_rotation = 0.0f;
}

void update_camera(game_t *game)
{
    game->camera.target_x = game->player.pos.x * TILE_SIZE - WINDOW_WIDTH / 2;
    game->camera.target_y = game->player.pos.y * TILE_SIZE - WINDOW_HEIGHT / 2;
    
    game->camera.x += (game->camera.target_x - game->camera.x) * 0.1f;
    game->camera.y += (game->camera.target_y - game->camera.y) * 0.1f;
    game->camera.zoom += (game->camera.target_zoom - game->camera.zoom) * 0.05f;
    game->camera.rotation += (game->camera.target_rotation - game->camera.rotation) * 0.05f;
    
    if (game->camera.x < 0)
        game->camera.x = 0;
    if (game->camera.y < 0)
        game->camera.y = 0;
    if (game->camera.x > MAP_WIDTH * TILE_SIZE - WINDOW_WIDTH)
        game->camera.x = MAP_WIDTH * TILE_SIZE - WINDOW_WIDTH;
    if (game->camera.y > MAP_HEIGHT * TILE_SIZE - WINDOW_HEIGHT)
        game->camera.y = MAP_HEIGHT * TILE_SIZE - WINDOW_HEIGHT;
}

void camera_zoom(game_t *game, float zoom_factor)
{
    game->camera.target_zoom = zoom_factor;
    
    if (game->camera.target_zoom < 0.5f)
        game->camera.target_zoom = 0.5f;
    if (game->camera.target_zoom > 2.0f)
        game->camera.target_zoom = 2.0f;
}

void camera_rotate(game_t *game, float angle)
{
    game->camera.target_rotation = angle;
    
    while (game->camera.target_rotation < 0)
        game->camera.target_rotation += 360.0f;
    while (game->camera.target_rotation >= 360.0f)
        game->camera.target_rotation -= 360.0f;
}

sfVector2f world_to_screen(game_t *game, vector2_t world_pos)
{
    sfVector2f screen_pos;
    
    float cos_rot = cos(game->camera.rotation * M_PI / 180.0f);
    float sin_rot = sin(game->camera.rotation * M_PI / 180.0f);
    
    float rel_x = (world_pos.x * TILE_SIZE - game->camera.x) * game->camera.zoom;
    float rel_y = (world_pos.y * TILE_SIZE - game->camera.y) * game->camera.zoom;
    
    screen_pos.x = rel_x * cos_rot - rel_y * sin_rot + WINDOW_WIDTH / 2;
    screen_pos.y = rel_x * sin_rot + rel_y * cos_rot + WINDOW_HEIGHT / 2;
    
    return screen_pos;
}

vector2_t screen_to_world(game_t *game, sfVector2f screen_pos)
{
    vector2_t world_pos;
    
    float cos_rot = cos(-game->camera.rotation * M_PI / 180.0f);
    float sin_rot = sin(-game->camera.rotation * M_PI / 180.0f);
    
    float rel_x = (screen_pos.x - WINDOW_WIDTH / 2);
    float rel_y = (screen_pos.y - WINDOW_HEIGHT / 2);
    
    float rotated_x = rel_x * cos_rot - rel_y * sin_rot;
    float rotated_y = rel_x * sin_rot + rel_y * cos_rot;
    
    world_pos.x = (rotated_x / game->camera.zoom + game->camera.x) / TILE_SIZE;
    world_pos.y = (rotated_y / game->camera.zoom + game->camera.y) / TILE_SIZE;
    
    return world_pos;
}