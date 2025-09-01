/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Camera system for 3D projection
*/

#include "../include/my_world.h"

void init_camera(world_t *world)
{
    if (!world)
        return;
    
    world->camera.pos = (vector3_t){0, 0, 10};
    world->camera.target = (vector3_t){16, 16, 0};
    world->camera.zoom = 1.0f;
    world->camera.rotation_x = -30.0f;
    world->camera.rotation_y = 45.0f;
}

void update_camera(world_t *world)
{
    if (!world)
        return;
    
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(world->window);
    
    if (mouse_pos.x < 50 || mouse_pos.x > WINDOW_WIDTH - 50 ||
        mouse_pos.y < 50 || mouse_pos.y > WINDOW_HEIGHT - 50) {
        
        float move_speed = 200.0f * world->delta_time;
        
        if (mouse_pos.x < 50)
            world->camera.target.x -= move_speed;
        if (mouse_pos.x > WINDOW_WIDTH - 50)
            world->camera.target.x += move_speed;
        if (mouse_pos.y < 50)
            world->camera.target.y -= move_speed;
        if (mouse_pos.y > WINDOW_HEIGHT - 50)
            world->camera.target.y += move_speed;
    }
    
    if (world->camera.target.x < 0)
        world->camera.target.x = 0;
    if (world->camera.target.y < 0)
        world->camera.target.y = 0;
    if (world->camera.target.x > world->map.width)
        world->camera.target.x = world->map.width;
    if (world->camera.target.y > world->map.height)
        world->camera.target.y = world->map.height;
}

vector2_t world_to_screen(world_t *world, vector3_t world_pos)
{
    if (!world)
        return (vector2_t){0, 0};
    
    vector3_t relative_pos;
    relative_pos.x = world_pos.x - world->camera.target.x;
    relative_pos.y = world_pos.y - world->camera.target.y;
    relative_pos.z = world_pos.z;
    
    vector2_t iso_pos = isometric_projection(relative_pos);
    
    iso_pos.x *= world->camera.zoom * TILE_SIZE;
    iso_pos.y *= world->camera.zoom * TILE_SIZE;
    
    iso_pos.x += WINDOW_WIDTH / 2;
    iso_pos.y += WINDOW_HEIGHT / 2;
    
    return iso_pos;
}

vector3_t screen_to_world(world_t *world, vector2_t screen_pos)
{
    if (!world)
        return (vector3_t){0, 0, 0};
    
    float rel_x = (screen_pos.x - WINDOW_WIDTH / 2) / (world->camera.zoom * TILE_SIZE);
    float rel_y = (screen_pos.y - WINDOW_HEIGHT / 2) / (world->camera.zoom * TILE_SIZE);
    
    vector3_t world_pos;
    world_pos.x = (rel_x + rel_y) / 2.0f + world->camera.target.x;
    world_pos.y = (rel_y - rel_x) / 2.0f + world->camera.target.y;
    world_pos.z = 0;
    
    return world_pos;
}

vector2_t isometric_projection(vector3_t pos)
{
    vector2_t result;
    
    result.x = (pos.x - pos.y);
    result.y = (pos.x + pos.y) * 0.5f - pos.z;
    
    return result;
}