/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Map management system
*/

#include "../include/my_world.h"

void init_map(world_t *world, int width, int height)
{
    if (!world || width <= 0 || height <= 0)
        return;
    
    world->map.width = (width > MAP_MAX_SIZE) ? MAP_MAX_SIZE : width;
    world->map.height = (height > MAP_MAX_SIZE) ? MAP_MAX_SIZE : height;
    world->map.modified = 0;
    strcpy(world->map.filename, "untitled.legend");
    
    world->map.tiles = malloc(sizeof(tile_t*) * world->map.height);
    if (!world->map.tiles)
        return;
    
    for (int y = 0; y < world->map.height; y++) {
        world->map.tiles[y] = malloc(sizeof(tile_t) * world->map.width);
        if (!world->map.tiles[y])
            continue;
        
        for (int x = 0; x < world->map.width; x++) {
            world->map.tiles[y][x].height = 0.0f;
            world->map.tiles[y][x].selected = 0;
            world->map.tiles[y][x].color = sfColor_fromRGB(100, 200, 100);
            world->map.tiles[y][x].texture = NULL;
            
            for (int i = 0; i < 4; i++) {
                world->map.tiles[y][x].corners[i].x = x + (i % 2);
                world->map.tiles[y][x].corners[i].y = y + (i / 2);
                world->map.tiles[y][x].corners[i].z = 0.0f;
            }
        }
    }
}

void destroy_map(map_t *map)
{
    if (!map || !map->tiles)
        return;
    
    for (int y = 0; y < map->height; y++) {
        if (map->tiles[y])
            free(map->tiles[y]);
    }
    
    free(map->tiles);
    map->tiles = NULL;
}

void generate_default_map(world_t *world)
{
    if (!world || !world->map.tiles)
        return;
    
    srand(42);
    
    for (int y = 0; y < world->map.height; y++) {
        for (int x = 0; x < world->map.width; x++) {
            float height = sin(x * 0.2f) * cos(y * 0.2f) * 2.0f;
            height += (rand() % 100) / 100.0f - 0.5f;
            
            world->map.tiles[y][x].height = height;
            
            for (int i = 0; i < 4; i++) {
                world->map.tiles[y][x].corners[i].z = height;
            }
            
            if (height < -1.0f) {
                world->map.tiles[y][x].color = sfColor_fromRGB(50, 150, 255);
            } else if (height > 2.0f) {
                world->map.tiles[y][x].color = sfColor_fromRGB(150, 150, 150);
            } else {
                world->map.tiles[y][x].color = sfColor_fromRGB(100, 200, 100);
            }
        }
    }
}

void save_map(world_t *world, const char *filename)
{
    if (!world || !filename || !world->map.tiles)
        return;
    
    FILE *file = fopen(filename, "w");
    if (!file)
        return;
    
    fprintf(file, "# MyWorld Map File\n");
    fprintf(file, "# Width Height\n");
    fprintf(file, "%d %d\n", world->map.width, world->map.height);
    fprintf(file, "# Tile heights\n");
    
    for (int y = 0; y < world->map.height; y++) {
        for (int x = 0; x < world->map.width; x++) {
            fprintf(file, "%.2f", world->map.tiles[y][x].height);
            if (x < world->map.width - 1)
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    world->map.modified = 0;
    strcpy(world->map.filename, filename);
}

int load_map(world_t *world, const char *filename)
{
    if (!world || !filename)
        return 84;
    
    FILE *file = fopen(filename, "r");
    if (!file)
        return 84;
    
    char line[1024];
    int width = 0, height = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n')
            continue;
        
        if (width == 0 && height == 0) {
            if (sscanf(line, "%d %d", &width, &height) != 2) {
                fclose(file);
                return 84;
            }
            
            destroy_map(&world->map);
            init_map(world, width, height);
            continue;
        }
        
        break;
    }
    
    for (int y = 0; y < world->map.height; y++) {
        if (!fgets(line, sizeof(line), file)) {
            fclose(file);
            return 84;
        }
        
        char *token = strtok(line, " \t\n");
        for (int x = 0; x < world->map.width && token; x++) {
            world->map.tiles[y][x].height = atof(token);
            
            for (int i = 0; i < 4; i++) {
                world->map.tiles[y][x].corners[i].z = world->map.tiles[y][x].height;
            }
            
            token = strtok(NULL, " \t\n");
        }
    }
    
    fclose(file);
    strcpy(world->map.filename, filename);
    world->map.modified = 0;
    
    return 0;
}