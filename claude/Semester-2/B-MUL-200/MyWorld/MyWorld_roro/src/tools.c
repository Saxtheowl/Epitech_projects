/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Terrain modification tools
*/

#include "../include/my_world.h"

void apply_tool(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    switch (world->current_tool) {
        case TOOL_RAISE:
            tool_raise(world, x, y);
            break;
        case TOOL_LOWER:
            tool_lower(world, x, y);
            break;
        case TOOL_FLATTEN:
            tool_flatten(world, x, y);
            break;
        case TOOL_SMOOTH:
            tool_smooth(world, x, y);
            break;
        case TOOL_NOISE:
            tool_noise(world, x, y);
            break;
        case TOOL_RESET:
            tool_reset(world, x, y);
            break;
        default:
            break;
    }
    
    world->map.modified = 1;
}

void tool_raise(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    int size = world->ui.effect_size;
    float strength = 0.1f;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < world->map.width &&
                ny >= 0 && ny < world->map.height) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    world->map.tiles[ny][nx].height += strength * falloff;
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                    
                    if (world->map.tiles[ny][nx].height > 5.0f) {
                        world->map.tiles[ny][nx].color = sfColor_fromRGB(150, 150, 150);
                    } else if (world->map.tiles[ny][nx].height > 0.0f) {
                        world->map.tiles[ny][nx].color = sfColor_fromRGB(100, 200, 100);
                    }
                }
            }
        }
    }
}

void tool_lower(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    int size = world->ui.effect_size;
    float strength = 0.1f;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < world->map.width &&
                ny >= 0 && ny < world->map.height) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    world->map.tiles[ny][nx].height -= strength * falloff;
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                    
                    if (world->map.tiles[ny][nx].height < -1.0f) {
                        world->map.tiles[ny][nx].color = sfColor_fromRGB(50, 150, 255);
                    } else if (world->map.tiles[ny][nx].height < 0.0f) {
                        world->map.tiles[ny][nx].color = sfColor_fromRGB(150, 180, 100);
                    }
                }
            }
        }
    }
}

void tool_flatten(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles || x < 0 || x >= world->map.width ||
        y < 0 || y >= world->map.height)
        return;
    
    float target_height = world->map.tiles[y][x].height;
    int size = world->ui.effect_size;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < world->map.width &&
                ny >= 0 && ny < world->map.height) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    float current_height = world->map.tiles[ny][nx].height;
                    world->map.tiles[ny][nx].height = current_height + 
                        (target_height - current_height) * falloff * 0.1f;
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                }
            }
        }
    }
}

void tool_smooth(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    int size = world->ui.effect_size;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 1 && nx < world->map.width - 1 &&
                ny >= 1 && ny < world->map.height - 1) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    float avg_height = 0;
                    int count = 0;
                    
                    for (int sy = -1; sy <= 1; sy++) {
                        for (int sx = -1; sx <= 1; sx++) {
                            avg_height += world->map.tiles[ny + sy][nx + sx].height;
                            count++;
                        }
                    }
                    
                    avg_height /= count;
                    
                    float current_height = world->map.tiles[ny][nx].height;
                    world->map.tiles[ny][nx].height = current_height + 
                        (avg_height - current_height) * falloff * 0.1f;
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                }
            }
        }
    }
}

void tool_noise(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    int size = world->ui.effect_size;
    float strength = 0.5f;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < world->map.width &&
                ny >= 0 && ny < world->map.height) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    float noise_value = (rand() % 200 - 100) / 100.0f;
                    world->map.tiles[ny][nx].height += noise_value * strength * falloff;
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                }
            }
        }
    }
}

void tool_reset(world_t *world, int x, int y)
{
    if (!world || !world->map.tiles)
        return;
    
    int size = world->ui.effect_size;
    
    for (int dy = -size; dy <= size; dy++) {
        for (int dx = -size; dx <= size; dx++) {
            int nx = x + dx;
            int ny = y + dy;
            
            if (nx >= 0 && nx < world->map.width &&
                ny >= 0 && ny < world->map.height) {
                
                float distance = sqrt(dx * dx + dy * dy);
                float falloff = 1.0f - (distance / size);
                
                if (falloff > 0) {
                    world->map.tiles[ny][nx].height *= (1.0f - falloff * 0.1f);
                    
                    for (int i = 0; i < 4; i++) {
                        world->map.tiles[ny][nx].corners[i].z = world->map.tiles[ny][nx].height;
                    }
                    
                    world->map.tiles[ny][nx].color = sfColor_fromRGB(100, 200, 100);
                }
            }
        }
    }
}