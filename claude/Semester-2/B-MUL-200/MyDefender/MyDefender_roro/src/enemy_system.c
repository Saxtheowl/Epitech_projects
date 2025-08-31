/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Enemy spawning and movement system
*/

#include "../include/my_defender.h"

void init_enemy_system(game_t *game)
{
    game->enemies = NULL;
}

void spawn_enemy(game_t *game, enemy_type_t type)
{
    enemy_t *enemy = malloc(sizeof(enemy_t));
    if (!enemy)
        return;
    
    enemy->type = type;
    enemy->pos = (sfVector2f){-GRID_SIZE, (MAP_HEIGHT/2) * GRID_SIZE};
    enemy->target_pos = (sfVector2f){MAP_WIDTH * GRID_SIZE, (MAP_HEIGHT/2) * GRID_SIZE};
    
    switch (type) {
        case ENEMY_BASIC:
            enemy->hp = 50;
            enemy->max_hp = 50;
            enemy->speed = 30.0f;
            enemy->reward = 25;
            break;
        case ENEMY_FAST:
            enemy->hp = 25;
            enemy->max_hp = 25;
            enemy->speed = 60.0f;
            enemy->reward = 30;
            break;
        case ENEMY_TANK:
            enemy->hp = 150;
            enemy->max_hp = 150;
            enemy->speed = 15.0f;
            enemy->reward = 50;
            break;
        default:
            break;
    }
    
    enemy->move_clock = sfClock_create();
    enemy->sprite = sfSprite_create();
    
    if (enemy->sprite && game->textures[5 + type]) {
        sfSprite_setTexture(enemy->sprite, game->textures[5 + type], sfFalse);
        sfSprite_setPosition(enemy->sprite, enemy->pos);
    }
    
    enemy->next = game->enemies;
    game->enemies = enemy;
}

void update_enemies(game_t *game)
{
    enemy_t *enemy = game->enemies;
    enemy_t *prev = NULL;
    
    while (enemy) {
        move_enemy(enemy);
        
        if (enemy->sprite) {
            sfSprite_setPosition(enemy->sprite, enemy->pos);
        }
        
        if (enemy->pos.x >= MAP_WIDTH * GRID_SIZE) {
            game->castle_hp -= 10;
            play_sound(game, 2);
            
            if (prev) {
                prev->next = enemy->next;
            } else {
                game->enemies = enemy->next;
            }
            
            enemy_t *to_delete = enemy;
            enemy = enemy->next;
            
            if (to_delete->sprite)
                sfSprite_destroy(to_delete->sprite);
            if (to_delete->move_clock)
                sfClock_destroy(to_delete->move_clock);
            free(to_delete);
            continue;
        }
        
        if (enemy->hp <= 0) {
            game->money += enemy->reward;
            game->score += enemy->reward;
            game->enemies_killed++;
            play_sound(game, 1);
            
            if (prev) {
                prev->next = enemy->next;
            } else {
                game->enemies = enemy->next;
            }
            
            enemy_t *to_delete = enemy;
            enemy = enemy->next;
            
            if (to_delete->sprite)
                sfSprite_destroy(to_delete->sprite);
            if (to_delete->move_clock)
                sfClock_destroy(to_delete->move_clock);
            free(to_delete);
            continue;
        }
        
        prev = enemy;
        enemy = enemy->next;
    }
}

void render_enemies(game_t *game)
{
    enemy_t *enemy = game->enemies;
    
    while (enemy) {
        if (enemy->sprite) {
            sfRenderWindow_drawSprite(game->window, enemy->sprite, NULL);
        } else {
            sfCircleShape *circle = sfCircleShape_create();
            if (circle) {
                sfCircleShape_setRadius(circle, GRID_SIZE/2 - 2);
                sfCircleShape_setOrigin(circle, (sfVector2f){GRID_SIZE/2 - 2, GRID_SIZE/2 - 2});
                sfCircleShape_setPosition(circle, (sfVector2f){
                    enemy->pos.x + GRID_SIZE/2, 
                    enemy->pos.y + GRID_SIZE/2
                });
                
                sfColor color;
                switch (enemy->type) {
                    case ENEMY_BASIC:
                        color = sfColor_fromRGB(255, 0, 0);
                        break;
                    case ENEMY_FAST:
                        color = sfColor_fromRGB(255, 255, 0);
                        break;
                    case ENEMY_TANK:
                        color = sfColor_fromRGB(128, 0, 128);
                        break;
                    default:
                        color = sfRed;
                        break;
                }
                
                sfCircleShape_setFillColor(circle, color);
                sfRenderWindow_drawCircleShape(game->window, circle, NULL);
                sfCircleShape_destroy(circle);
            }
        }
        
        if (enemy->hp < enemy->max_hp) {
            sfRectangleShape *bg = sfRectangleShape_create();
            sfRectangleShape *health = sfRectangleShape_create();
            
            if (bg && health) {
                float bar_width = GRID_SIZE - 4;
                float health_width = (float)enemy->hp / enemy->max_hp * bar_width;
                
                sfRectangleShape_setSize(bg, (sfVector2f){bar_width, 4});
                sfRectangleShape_setPosition(bg, (sfVector2f){enemy->pos.x + 2, enemy->pos.y - 8});
                sfRectangleShape_setFillColor(bg, sfRed);
                
                sfRectangleShape_setSize(health, (sfVector2f){health_width, 4});
                sfRectangleShape_setPosition(health, (sfVector2f){enemy->pos.x + 2, enemy->pos.y - 8});
                sfRectangleShape_setFillColor(health, sfGreen);
                
                sfRenderWindow_drawRectangleShape(game->window, bg, NULL);
                sfRenderWindow_drawRectangleShape(game->window, health, NULL);
                
                sfRectangleShape_destroy(bg);
                sfRectangleShape_destroy(health);
            }
        }
        
        enemy = enemy->next;
    }
}

void move_enemy(enemy_t *enemy)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(enemy->move_clock));
    float distance_to_move = enemy->speed * elapsed;
    
    enemy->pos.x += distance_to_move;
    
    sfClock_restart(enemy->move_clock);
}

enemy_t *get_nearest_enemy(game_t *game, sfVector2f pos, float range)
{
    enemy_t *nearest = NULL;
    float nearest_distance = range + 1;
    
    enemy_t *enemy = game->enemies;
    while (enemy) {
        float dist = distance(pos, (sfVector2f){
            enemy->pos.x + GRID_SIZE/2, 
            enemy->pos.y + GRID_SIZE/2
        });
        
        if (dist <= range && dist < nearest_distance) {
            nearest = enemy;
            nearest_distance = dist;
        }
        
        enemy = enemy->next;
    }
    
    return nearest;
}