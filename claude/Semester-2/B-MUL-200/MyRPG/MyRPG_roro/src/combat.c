/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Combat system implementation
*/

#include "../include/my_rpg.h"

void init_combat(game_t *game, enemy_t *enemy)
{
    game->combat_enemy = enemy;
    game->combat_turn = 0;
    
    spawn_particle(game, enemy->pos, PARTICLE_FIRE);
    play_sound(game, 5);
}

void process_combat_turn(game_t *game)
{
    if (!game->combat_enemy || !game->combat_enemy->alive) {
        end_combat(game);
        return;
    }
    
    game->combat_turn = (game->combat_turn + 1) % 2;
    
    if (game->combat_turn == 1) {
        enemy_attack(game, game->combat_enemy);
        
        if (game->player.stats.health <= 0) {
            game->current_scene = SCENE_GAME_OVER;
            return;
        }
    }
    
    if (!game->combat_enemy->alive) {
        end_combat(game);
    }
}

void end_combat(game_t *game)
{
    game->combat_enemy = NULL;
    game->combat_turn = 0;
    game->current_scene = SCENE_GAME;
    
    if (game->player.stats.health > 0) {
        spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
    }
}

int calculate_damage(stats_t *attacker, stats_t *defender)
{
    int base_damage = attacker->strength;
    int defense = defender->defense;
    
    int damage = base_damage - defense / 2;
    
    if (damage < 1)
        damage = 1;
    
    int variance = random_int(-damage / 4, damage / 4);
    damage += variance;
    
    if (damage < 1)
        damage = 1;
    
    return damage;
}