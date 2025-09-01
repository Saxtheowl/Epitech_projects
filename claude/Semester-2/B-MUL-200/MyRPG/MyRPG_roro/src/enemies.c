/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Enemy AI and combat system
*/

#include "../include/my_rpg.h"

void init_enemies(game_t *game)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        game->enemies[i].alive = 0;
        game->enemies[i].sprite = NULL;
        game->enemies[i].ai_clock = sfClock_create();
    }
    
    for (int i = 0; i < 5; i++) {
        game->enemies[i].id = i;
        sprintf(game->enemies[i].name, "Goblin %d", i + 1);
        game->enemies[i].pos.x = 10.0f + i * 3.0f;
        game->enemies[i].pos.y = 10.0f + i * 2.0f;
        game->enemies[i].alive = 1;
        game->enemies[i].aggressive = 1;
        game->enemies[i].detection_range = 5.0f;
        
        game->enemies[i].stats.level = 1 + i;
        game->enemies[i].stats.health = 30 + i * 10;
        game->enemies[i].stats.max_health = 30 + i * 10;
        game->enemies[i].stats.strength = 5 + i;
        game->enemies[i].stats.defense = 2 + i;
        game->enemies[i].stats.agility = 3 + i;
        
        game->enemies[i].sprite = sfSprite_create();
        if (game->enemies[i].sprite && game->textures[1]) {
            sfSprite_setTexture(game->enemies[i].sprite, game->textures[1], sfFalse);
        }
    }
    
    for (int i = 5; i < 10; i++) {
        game->enemies[i].id = i;
        sprintf(game->enemies[i].name, "Orc %d", i - 4);
        game->enemies[i].pos.x = 15.0f + (i - 5) * 4.0f;
        game->enemies[i].pos.y = 15.0f + (i - 5) * 3.0f;
        game->enemies[i].alive = 1;
        game->enemies[i].aggressive = 1;
        game->enemies[i].detection_range = 6.0f;
        
        game->enemies[i].stats.level = 3 + (i - 5);
        game->enemies[i].stats.health = 60 + (i - 5) * 15;
        game->enemies[i].stats.max_health = 60 + (i - 5) * 15;
        game->enemies[i].stats.strength = 8 + (i - 5) * 2;
        game->enemies[i].stats.defense = 4 + (i - 5);
        game->enemies[i].stats.agility = 2 + (i - 5);
        
        game->enemies[i].sprite = sfSprite_create();
        if (game->enemies[i].sprite && game->textures[2]) {
            sfSprite_setTexture(game->enemies[i].sprite, game->textures[2], sfFalse);
        }
    }
}

void update_enemies(game_t *game)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].alive) {
            enemy_ai(game, &game->enemies[i]);
        }
    }
}

void enemy_ai(game_t *game, enemy_t *enemy)
{
    if (!enemy || !enemy->alive)
        return;
    
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(enemy->ai_clock));
    if (elapsed < 0.5f)
        return;
    
    if (enemy_can_see_player(game, enemy)) {
        vector2_t direction;
        direction.x = game->player.pos.x - enemy->pos.x;
        direction.y = game->player.pos.y - enemy->pos.y;
        
        float dist = distance(enemy->pos, game->player.pos);
        
        if (dist < 1.5f) {
            if (enemy->aggressive) {
                enemy_attack(game, enemy);
            }
        } else if (dist < enemy->detection_range) {
            direction = normalize(direction);
            
            vector2_t new_pos;
            new_pos.x = enemy->pos.x + direction.x * 0.5f;
            new_pos.y = enemy->pos.y + direction.y * 0.5f;
            
            if (!check_map_collision(game, new_pos)) {
                enemy->pos = new_pos;
            }
        }
    } else {
        if (random_int(0, 100) < 20) {
            vector2_t random_direction;
            random_direction.x = (float)random_int(-1, 1);
            random_direction.y = (float)random_int(-1, 1);
            
            if (random_direction.x != 0 || random_direction.y != 0) {
                random_direction = normalize(random_direction);
                
                vector2_t new_pos;
                new_pos.x = enemy->pos.x + random_direction.x * 0.3f;
                new_pos.y = enemy->pos.y + random_direction.y * 0.3f;
                
                if (!check_map_collision(game, new_pos)) {
                    enemy->pos = new_pos;
                }
            }
        }
    }
    
    sfClock_restart(enemy->ai_clock);
}

void enemy_attack(game_t *game, enemy_t *enemy)
{
    if (!enemy || !enemy->alive)
        return;
    
    int damage = calculate_damage(&enemy->stats, &game->player.stats);
    game->player.stats.health -= damage;
    
    spawn_particle(game, game->player.pos, PARTICLE_BLOOD);
    play_sound(game, 4);
    
    if (game->player.stats.health <= 0) {
        game->current_scene = SCENE_GAME_OVER;
    }
}

int enemy_can_see_player(game_t *game, enemy_t *enemy)
{
    if (!enemy || !enemy->alive)
        return 0;
    
    float dist = distance(enemy->pos, game->player.pos);
    
    if (dist > enemy->detection_range)
        return 0;
    
    vector2_t direction = normalize((vector2_t){
        game->player.pos.x - enemy->pos.x,
        game->player.pos.y - enemy->pos.y
    });
    
    vector2_t check_pos = enemy->pos;
    float step_size = 0.5f;
    
    while (distance(check_pos, game->player.pos) > step_size) {
        check_pos.x += direction.x * step_size;
        check_pos.y += direction.y * step_size;
        
        if (check_map_collision(game, check_pos)) {
            return 0;
        }
    }
    
    return 1;
}