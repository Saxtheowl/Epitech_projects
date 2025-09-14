/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Player management functions for MyRunner project
*/

#include "my_runner.h"

int init_player(game_t *game)
{
    // Initialize player structure
    game->player.position.x = 100;
    game->player.position.y = GROUND_LEVEL - PLAYER_HEIGHT;
    game->player.velocity.x = 0;
    game->player.velocity.y = 0;
    game->player.on_ground = 1;
    game->player.alive = 1;
    game->player.animation_frame = 0;
    game->player.max_frames = 4;
    
    // Create player texture (simple colored rectangle if no texture file)
    game->player.texture = sfTexture_create(PLAYER_WIDTH, PLAYER_HEIGHT);
    if (!game->player.texture)
        return -1;
    
    // Create player sprite
    game->player.sprite = sfSprite_create();
    if (!game->player.sprite)
        return -1;
    sfSprite_setTexture(game->player.sprite, game->player.texture, sfTrue);
    
    // Create hitbox
    game->player.hitbox = sfRectangleShape_create();
    if (!game->player.hitbox)
        return -1;
        
    sfVector2f size = {PLAYER_WIDTH - 10, PLAYER_HEIGHT - 10};
    sfRectangleShape_setSize(game->player.hitbox, size);
    sfRectangleShape_setFillColor(game->player.hitbox, sfBlue);
    sfRectangleShape_setOutlineThickness(game->player.hitbox, 2);
    sfRectangleShape_setOutlineColor(game->player.hitbox, sfWhite);
    
    // Create animation clock
    game->player.animation_clock = sfClock_create();
    if (!game->player.animation_clock)
        return -1;
    
    return 0;
}

void update_player(game_t *game, float delta_time)
{
    if (!game->player.alive)
        return;
    
    // Apply gravity
    apply_gravity(&game->player, delta_time);
    
    // Update position
    game->player.position.y += game->player.velocity.y * delta_time;
    
    // Check ground collision
    if (game->player.position.y >= GROUND_LEVEL - PLAYER_HEIGHT) {
        game->player.position.y = GROUND_LEVEL - PLAYER_HEIGHT;
        game->player.velocity.y = 0;
        game->player.on_ground = 1;
    }
    
    // Update sprite position
    sfSprite_setPosition(game->player.sprite, game->player.position);
    
    // Update hitbox position
    sfVector2f hitbox_pos = {
        game->player.position.x + 5,
        game->player.position.y + 5
    };
    sfRectangleShape_setPosition(game->player.hitbox, hitbox_pos);
    
    // Update animation
    if (sfTime_asSeconds(sfClock_getElapsedTime(game->player.animation_clock)) > 0.2f) {
        game->player.animation_frame = (game->player.animation_frame + 1) % game->player.max_frames;
        sfClock_restart(game->player.animation_clock);
    }
}

void draw_player(game_t *game)
{
    if (!game->player.alive)
        return;
        
    sfRenderWindow_drawSprite(game->window, game->player.sprite, NULL);
    // Uncomment to show hitbox for debugging
    // sfRenderWindow_drawRectangleShape(game->window, game->player.hitbox, NULL);
}

void player_jump(game_t *game)
{
    if (game->player.on_ground && game->player.alive) {
        game->player.velocity.y = JUMP_FORCE;
        game->player.on_ground = 0;
        
        // Play jump sound if available
        if (game->jump_sound)
            sfSound_play(game->jump_sound);
    }
}