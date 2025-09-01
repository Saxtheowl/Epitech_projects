/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Rendering system for 3D map visualization
*/

#include "../include/my_world.h"

void render_map(world_t *world)
{
    if (!world || !world->map.tiles)
        return;
    
    for (int y = 0; y < world->map.height; y++) {
        for (int x = 0; x < world->map.width; x++) {
            render_tile(world, &world->map.tiles[y][x], x, y);
        }
    }
    
    render_wireframe(world);
}

void render_tile(world_t *world, tile_t *tile, int x, int y)
{
    if (!world || !tile)
        return;
    
    vector3_t corners[4];
    corners[0] = (vector3_t){x, y, tile->height};
    corners[1] = (vector3_t){x + 1, y, tile->height};
    corners[2] = (vector3_t){x + 1, y + 1, tile->height};
    corners[3] = (vector3_t){x, y + 1, tile->height};
    
    vector2_t screen_corners[4];
    for (int i = 0; i < 4; i++) {
        screen_corners[i] = world_to_screen(world, corners[i]);
    }
    
    sfConvexShape *shape = sfConvexShape_create();
    if (!shape)
        return;
    
    sfConvexShape_setPointCount(shape, 4);
    
    for (int i = 0; i < 4; i++) {
        sfConvexShape_setPoint(shape, i, 
            (sfVector2f){screen_corners[i].x, screen_corners[i].y});
    }
    
    sfColor color = tile->color;
    if (tile->selected) {
        color = sfColor_fromRGB(
            color.r + 50 > 255 ? 255 : color.r + 50,
            color.g + 50 > 255 ? 255 : color.g + 50,
            color.b + 50 > 255 ? 255 : color.b + 50
        );
    }
    
    float depth_factor = (tile->height + 5.0f) / 10.0f;
    if (depth_factor < 0.3f) depth_factor = 0.3f;
    if (depth_factor > 1.0f) depth_factor = 1.0f;
    
    color.r = (unsigned char)(color.r * depth_factor);
    color.g = (unsigned char)(color.g * depth_factor);
    color.b = (unsigned char)(color.b * depth_factor);
    
    sfConvexShape_setFillColor(shape, color);
    sfConvexShape_setOutlineThickness(shape, 1);
    sfConvexShape_setOutlineColor(shape, sfColor_fromRGB(80, 80, 80));
    
    sfRenderWindow_drawConvexShape(world->window, shape, NULL);
    sfConvexShape_destroy(shape);
}

void render_wireframe(world_t *world)
{
    if (!world || !world->map.tiles)
        return;
    
    for (int y = 0; y < world->map.height; y++) {
        for (int x = 0; x < world->map.width; x++) {
            vector3_t pos = (vector3_t){x, y, world->map.tiles[y][x].height};
            vector2_t screen_pos = world_to_screen(world, pos);
            
            if (x < world->map.width - 1) {
                vector3_t next_pos = (vector3_t){x + 1, y, world->map.tiles[y][x + 1].height};
                vector2_t next_screen = world_to_screen(world, next_pos);
                
                sfVertex line[2] = {
                    {{screen_pos.x, screen_pos.y}, sfColor_fromRGB(120, 120, 120), {0, 0}},
                    {{next_screen.x, next_screen.y}, sfColor_fromRGB(120, 120, 120), {0, 0}}
                };
                
                sfRenderWindow_drawPrimitives(world->window, line, 2, sfLines, NULL);
            }
            
            if (y < world->map.height - 1) {
                vector3_t next_pos = (vector3_t){x, y + 1, world->map.tiles[y + 1][x].height};
                vector2_t next_screen = world_to_screen(world, next_pos);
                
                sfVertex line[2] = {
                    {{screen_pos.x, screen_pos.y}, sfColor_fromRGB(120, 120, 120), {0, 0}},
                    {{next_screen.x, next_screen.y}, sfColor_fromRGB(120, 120, 120), {0, 0}}
                };
                
                sfRenderWindow_drawPrimitives(world->window, line, 2, sfLines, NULL);
            }
        }
    }
}