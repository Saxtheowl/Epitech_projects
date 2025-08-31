/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Enemy wave management system
*/

#include "../include/my_defender.h"

void init_wave_system(game_t *game)
{
    game->current_wave.enemy_count = 5;
    game->current_wave.enemy_type = ENEMY_BASIC;
    game->current_wave.spawn_delay = 1.0f;
    game->current_wave.spawned = 0;
    game->current_wave.spawn_clock = sfClock_create();
}

void update_wave_system(game_t *game)
{
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(game->current_wave.spawn_clock));
    
    if (game->current_wave.spawned < game->current_wave.enemy_count && 
        elapsed >= game->current_wave.spawn_delay) {
        
        spawn_enemy(game, game->current_wave.enemy_type);
        game->current_wave.spawned++;
        sfClock_restart(game->current_wave.spawn_clock);
    }
    
    if (game->current_wave.spawned >= game->current_wave.enemy_count && !game->enemies) {
        start_next_wave(game);
    }
}

void start_next_wave(game_t *game)
{
    game->wave_number++;
    game->money += 100;
    
    game->current_wave.enemy_count = 5 + (game->wave_number - 1) * 2;
    game->current_wave.spawned = 0;
    
    game->current_wave.spawn_delay = 1.0f - (game->wave_number - 1) * 0.05f;
    if (game->current_wave.spawn_delay < 0.3f)
        game->current_wave.spawn_delay = 0.3f;
    
    switch ((game->wave_number - 1) % 6) {
        case 0:
        case 1:
            game->current_wave.enemy_type = ENEMY_BASIC;
            break;
        case 2:
        case 3:
            game->current_wave.enemy_type = ENEMY_FAST;
            break;
        case 4:
        case 5:
            game->current_wave.enemy_type = ENEMY_TANK;
            break;
    }
    
    if (game->wave_number % 5 == 0) {
        for (int i = 0; i < 3; i++) {
            spawn_enemy(game, ENEMY_TANK);
        }
        for (int i = 0; i < 5; i++) {
            spawn_enemy(game, ENEMY_FAST);
        }
    }
    
    sfClock_restart(game->current_wave.spawn_clock);
}