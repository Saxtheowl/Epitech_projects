/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Building placement and management system
*/

#include "../include/my_defender.h"

void init_building_system(game_t *game)
{
    for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; i++) {
        game->buildings[i].type = BUILD_NONE;
        game->buildings[i].sprite = NULL;
        game->buildings[i].attack_clock = NULL;
    }
}

int get_building_cost(building_type_t type)
{
    switch (type) {
        case BUILD_WALL:
            return 50;
        case BUILD_BASIC_TOWER:
            return 100;
        case BUILD_SLOW_TOWER:
            return 150;
        case BUILD_HEAVY_TOWER:
            return 200;
        default:
            return 0;
    }
}

int place_building(game_t *game, int x, int y, building_type_t type)
{
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
        return 0;
    
    if (game->grid[y][x] != BUILD_NONE)
        return 0;
    
    if (game->building_count >= MAP_HEIGHT * MAP_WIDTH)
        return 0;
    
    game->grid[y][x] = type;
    
    building_t *building = &game->buildings[game->building_count];
    building->type = type;
    building->pos = (sfVector2i){x, y};
    
    switch (type) {
        case BUILD_WALL:
            building->hp = 200;
            building->damage = 0;
            building->range = 0;
            building->attack_speed = 0;
            break;
        case BUILD_BASIC_TOWER:
            building->hp = 100;
            building->damage = 25;
            building->range = 3.0f * GRID_SIZE;
            building->attack_speed = 1.0f;
            break;
        case BUILD_SLOW_TOWER:
            building->hp = 100;
            building->damage = 15;
            building->range = 4.0f * GRID_SIZE;
            building->attack_speed = 0.5f;
            break;
        case BUILD_HEAVY_TOWER:
            building->hp = 150;
            building->damage = 50;
            building->range = 2.5f * GRID_SIZE;
            building->attack_speed = 0.3f;
            break;
        default:
            break;
    }
    
    building->attack_clock = sfClock_create();
    building->sprite = sfSprite_create();
    
    if (building->sprite && game->textures[type]) {
        sfSprite_setTexture(building->sprite, game->textures[type], sfFalse);
        sfSprite_setPosition(building->sprite, (sfVector2f){x * GRID_SIZE, y * GRID_SIZE});
    }
    
    game->building_count++;
    return 1;
}

void update_buildings(game_t *game)
{
    for (int i = 0; i < game->building_count; i++) {
        building_t *building = &game->buildings[i];
        
        if (building->type != BUILD_WALL && building->damage > 0) {
            float attack_delay = 1.0f / building->attack_speed;
            float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(building->attack_clock));
            
            if (elapsed >= attack_delay) {
                building_attack(game, building);
                sfClock_restart(building->attack_clock);
            }
        }
    }
}

void render_buildings(game_t *game)
{
    for (int i = 0; i < game->building_count; i++) {
        building_t *building = &game->buildings[i];
        
        if (building->sprite) {
            sfRenderWindow_drawSprite(game->window, building->sprite, NULL);
        } else {
            sfRectangleShape *rect = sfRectangleShape_create();
            if (rect) {
                sfRectangleShape_setSize(rect, (sfVector2f){GRID_SIZE - 2, GRID_SIZE - 2});
                sfRectangleShape_setPosition(rect, (sfVector2f){
                    building->pos.x * GRID_SIZE + 1, 
                    building->pos.y * GRID_SIZE + 1
                });
                
                sfColor color;
                switch (building->type) {
                    case BUILD_WALL:
                        color = sfColor_fromRGB(139, 69, 19);
                        break;
                    case BUILD_BASIC_TOWER:
                        color = sfColor_fromRGB(128, 128, 128);
                        break;
                    case BUILD_SLOW_TOWER:
                        color = sfColor_fromRGB(0, 0, 255);
                        break;
                    case BUILD_HEAVY_TOWER:
                        color = sfColor_fromRGB(255, 0, 0);
                        break;
                    default:
                        color = sfWhite;
                        break;
                }
                
                sfRectangleShape_setFillColor(rect, color);
                sfRenderWindow_drawRectangleShape(game->window, rect, NULL);
                sfRectangleShape_destroy(rect);
            }
        }
        
        if (building->range > 0 && game->selected_building == building->type) {
            sfCircleShape *range_circle = sfCircleShape_create();
            if (range_circle) {
                sfCircleShape_setRadius(range_circle, building->range);
                sfCircleShape_setOrigin(range_circle, (sfVector2f){building->range, building->range});
                sfCircleShape_setPosition(range_circle, (sfVector2f){
                    building->pos.x * GRID_SIZE + GRID_SIZE/2,
                    building->pos.y * GRID_SIZE + GRID_SIZE/2
                });
                sfCircleShape_setFillColor(range_circle, sfColor_fromRGBA(255, 255, 255, 50));
                sfCircleShape_setOutlineThickness(range_circle, 1);
                sfCircleShape_setOutlineColor(range_circle, sfWhite);
                sfRenderWindow_drawCircleShape(game->window, range_circle, NULL);
                sfCircleShape_destroy(range_circle);
            }
        }
    }
}