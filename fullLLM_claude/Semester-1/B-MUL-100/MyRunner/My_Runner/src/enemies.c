/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Enemy management functions for MyRunner project
*/

#include "my_runner.h"

int init_enemies(game_t *game)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        game->enemies[i].sprite = NULL;
        game->enemies[i].texture = NULL;
        game->enemies[i].hitbox = NULL;
        game->enemies[i].animation_clock = NULL;
        game->enemies[i].position.x = 0;
        game->enemies[i].position.y = 0;
        game->enemies[i].velocity.x = -200.0f;
        game->enemies[i].velocity.y = 0;
        game->enemies[i].alive = 0;
        game->enemies[i].type = 0;
        game->enemies[i].animation_frame = 0;
    }
    
    return 0;
}

void update_enemies(game_t *game, float delta_time)
{
    // Spawn new enemies randomly
    if (get_random_float(0, 1) < ENEMY_SPAWN_RATE) {
        spawn_enemy(game);
    }
    
    // Update existing enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!game->enemies[i].alive)
            continue;
            
        // Move enemy
        game->enemies[i].position.x += game->enemies[i].velocity.x * delta_time;
        
        // Remove enemy if it goes off screen
        if (game->enemies[i].position.x < -64) {
            game->enemies[i].alive = 0;
            if (game->enemies[i].sprite) {
                sfSprite_destroy(game->enemies[i].sprite);
                game->enemies[i].sprite = NULL;
            }
            if (game->enemies[i].texture) {
                sfTexture_destroy(game->enemies[i].texture);
                game->enemies[i].texture = NULL;
            }
            if (game->enemies[i].hitbox) {
                sfRectangleShape_destroy(game->enemies[i].hitbox);
                game->enemies[i].hitbox = NULL;
            }
            if (game->enemies[i].animation_clock) {
                sfClock_destroy(game->enemies[i].animation_clock);
                game->enemies[i].animation_clock = NULL;
            }
            continue;
        }
        
        // Update sprite and hitbox positions
        if (game->enemies[i].sprite)
            sfSprite_setPosition(game->enemies[i].sprite, game->enemies[i].position);
        if (game->enemies[i].hitbox)
            sfRectangleShape_setPosition(game->enemies[i].hitbox, game->enemies[i].position);
        
        // Update animation
        if (game->enemies[i].animation_clock && 
            sfTime_asSeconds(sfClock_getElapsedTime(game->enemies[i].animation_clock)) > 0.3f) {
            game->enemies[i].animation_frame = (game->enemies[i].animation_frame + 1) % 2;
            sfClock_restart(game->enemies[i].animation_clock);
        }
    }
}

void draw_enemies(game_t *game)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].alive && game->enemies[i].sprite) {
            sfRenderWindow_drawSprite(game->window, game->enemies[i].sprite, NULL);
            // Uncomment to show hitboxes for debugging
            // if (game->enemies[i].hitbox)
            //     sfRenderWindow_drawRectangleShape(game->window, game->enemies[i].hitbox, NULL);
        }
    }
}

void spawn_enemy(game_t *game)
{
    // Find an inactive enemy slot
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!game->enemies[i].alive) {
            // Create enemy
            game->enemies[i].texture = sfTexture_create(32, 32);
            if (!game->enemies[i].texture)
                return;
                
            game->enemies[i].sprite = sfSprite_create();
            if (!game->enemies[i].sprite)
                return;
                
            sfSprite_setTexture(game->enemies[i].sprite, game->enemies[i].texture, sfTrue);
            
            // Create hitbox
            game->enemies[i].hitbox = sfRectangleShape_create();
            if (!game->enemies[i].hitbox)
                return;
                
            sfVector2f size = {30, 30};
            sfRectangleShape_setSize(game->enemies[i].hitbox, size);
            sfRectangleShape_setFillColor(game->enemies[i].hitbox, sfMagenta);
            sfRectangleShape_setOutlineThickness(game->enemies[i].hitbox, 1);
            sfRectangleShape_setOutlineColor(game->enemies[i].hitbox, sfWhite);
            
            // Set position (spawn off-screen to the right)
            game->enemies[i].position.x = WINDOW_WIDTH + 50;
            game->enemies[i].position.y = get_random_float(GROUND_LEVEL - 100, GROUND_LEVEL - 32);
            
            // Set velocity
            game->enemies[i].velocity.x = get_random_float(-300, -150);
            game->enemies[i].velocity.y = 0;
            
            // Set type and properties
            game->enemies[i].type = (int)get_random_float(0, 2);
            game->enemies[i].alive = 1;
            game->enemies[i].animation_frame = 0;
            
            // Create animation clock
            game->enemies[i].animation_clock = sfClock_create();
            
            break;
        }
    }
}