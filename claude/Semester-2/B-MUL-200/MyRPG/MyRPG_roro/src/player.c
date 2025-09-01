/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Player character implementation
*/

#include "../include/my_rpg.h"

void init_player(game_t *game)
{
    game->player.pos.x = 5.0f;
    game->player.pos.y = 5.0f;
    game->player.velocity.x = 0.0f;
    game->player.velocity.y = 0.0f;
    game->player.facing_direction = 0;
    
    game->player.stats.level = 1;
    game->player.stats.experience = 0;
    game->player.stats.exp_to_next = 100;
    game->player.stats.health = 100;
    game->player.stats.max_health = 100;
    game->player.stats.mana = 50;
    game->player.stats.max_mana = 50;
    game->player.stats.strength = 10;
    game->player.stats.defense = 5;
    game->player.stats.agility = 8;
    game->player.stats.intelligence = 6;
    game->player.stats.gold = 100;
    
    init_inventory(game);
    
    game->player.move_clock = sfClock_create();
    
    game->player.sprite = sfSprite_create();
    if (game->player.sprite && game->textures[0]) {
        sfSprite_setTexture(game->player.sprite, game->textures[0], sfFalse);
    }
}

void update_player(game_t *game)
{
    vector2_t new_pos = game->player.pos;
    new_pos.x += game->player.velocity.x;
    new_pos.y += game->player.velocity.y;
    
    if (!check_map_collision(game, new_pos)) {
        game->player.pos = new_pos;
    }
    
    game->player.velocity.x *= 0.8f;
    game->player.velocity.y *= 0.8f;
    
    if (fabs(game->player.velocity.x) < 0.1f)
        game->player.velocity.x = 0.0f;
    if (fabs(game->player.velocity.y) < 0.1f)
        game->player.velocity.y = 0.0f;
}

void move_player(game_t *game, vector2_t direction)
{
    float move_speed = 0.3f;
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(game->player.move_clock));
    
    if (elapsed < 0.1f)
        return;
    
    vector2_t normalized = normalize(direction);
    game->player.velocity.x += normalized.x * move_speed;
    game->player.velocity.y += normalized.y * move_speed;
    
    if (direction.x > 0) game->player.facing_direction = 0;
    else if (direction.x < 0) game->player.facing_direction = 1;
    else if (direction.y > 0) game->player.facing_direction = 2;
    else if (direction.y < 0) game->player.facing_direction = 3;
    
    sfClock_restart(game->player.move_clock);
}

void player_attack(game_t *game, enemy_t *enemy)
{
    if (!enemy || !enemy->alive)
        return;
    
    int damage = calculate_damage(&game->player.stats, &enemy->stats);
    enemy->stats.health -= damage;
    
    spawn_particle(game, enemy->pos, PARTICLE_BLOOD);
    play_sound(game, 1);
    
    if (enemy->stats.health <= 0) {
        enemy->alive = 0;
        
        int exp_reward = enemy->stats.level * 25;
        int gold_reward = enemy->stats.level * 10 + random_int(5, 15);
        
        player_gain_exp(game, exp_reward);
        game->player.stats.gold += gold_reward;
        
        spawn_particle(game, enemy->pos, PARTICLE_SPARKLE);
        play_sound(game, 2);
    }
}

void player_level_up(game_t *game)
{
    game->player.stats.level++;
    game->player.stats.exp_to_next = game->player.stats.level * 100;
    
    game->player.stats.max_health += 20;
    game->player.stats.max_mana += 10;
    game->player.stats.strength += 2;
    game->player.stats.defense += 1;
    game->player.stats.agility += 1;
    game->player.stats.intelligence += 1;
    
    game->player.stats.health = game->player.stats.max_health;
    game->player.stats.mana = game->player.stats.max_mana;
    
    spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
    play_sound(game, 3);
}

void player_gain_exp(game_t *game, int exp)
{
    game->player.stats.experience += exp;
    
    while (game->player.stats.experience >= game->player.stats.exp_to_next) {
        game->player.stats.experience -= game->player.stats.exp_to_next;
        player_level_up(game);
    }
}