/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Physics system for MyRunner project
*/

#include "my_runner.h"

void apply_gravity(player_t *player, float delta_time)
{
    if (!player->on_ground) {
        player->velocity.y += GRAVITY * delta_time;
    }
}

void handle_collisions(game_t *game)
{
    if (!game->player.alive)
        return;
    
    // Check collisions with enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].alive && 
            check_player_enemy_collision(&game->player, &game->enemies[i])) {
            game->player.alive = 0;
            game->game_over = 1;
            return;
        }
    }
    
    // Check collision with map hazards
    int player_tile_x = (int)(game->player.position.x + game->map.scroll_offset) / TILE_SIZE;
    int player_tile_y = (int)(game->player.position.y) / TILE_SIZE;
    
    // Check surrounding tiles for hazards (type 2 = spikes)
    for (int dy = 0; dy <= 2; dy++) {
        for (int dx = 0; dx <= 2; dx++) {
            int tile_type = get_tile_type(game, player_tile_x + dx, player_tile_y + dy);
            if (tile_type == 2) { // Spike tile
                // More precise collision detection for spikes
                float tile_x = (player_tile_x + dx) * TILE_SIZE - game->map.scroll_offset;
                float tile_y = (player_tile_y + dy) * TILE_SIZE;
                
                if (game->player.position.x < tile_x + TILE_SIZE &&
                    game->player.position.x + PLAYER_WIDTH > tile_x &&
                    game->player.position.y < tile_y + TILE_SIZE &&
                    game->player.position.y + PLAYER_HEIGHT > tile_y) {
                    game->player.alive = 0;
                    game->game_over = 1;
                    return;
                }
            }
        }
    }
}

int check_player_enemy_collision(player_t *player, enemy_t *enemy)
{
    return (player->position.x < enemy->position.x + 32 &&
            player->position.x + PLAYER_WIDTH > enemy->position.x &&
            player->position.y < enemy->position.y + 32 &&
            player->position.y + PLAYER_HEIGHT > enemy->position.y);
}