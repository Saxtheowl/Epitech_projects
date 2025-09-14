/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Duck management for MyHunter project
*/

#include "my_hunter.h"

int init_ducks(game_t *game)
{
    // Initialize all ducks
    for (int i = 0; i < MAX_DUCKS; i++) {
        game->ducks[i].texture = sfTexture_createFromFile("assets/duck.png", NULL);
        if (!game->ducks[i].texture) {
            // Create a simple colored rectangle if no texture
            game->ducks[i].texture = sfTexture_create(DUCK_SIZE, DUCK_SIZE);
            if (!game->ducks[i].texture)
                return 84;
        }
        
        game->ducks[i].sprite = sfSprite_create();
        if (!game->ducks[i].sprite)
            return 84;
            
        sfSprite_setTexture(game->ducks[i].sprite, game->ducks[i].texture, sfTrue);
        
        game->ducks[i].animation_clock = sfClock_create();
        if (!game->ducks[i].animation_clock)
            return 84;
            
        game->ducks[i].alive = 0;
        game->ducks[i].animation_frame = 0;
        
        // Spawn first few ducks
        if (i < 2) {
            spawn_duck(game, i);
        }
    }
    
    return 0;
}

void spawn_duck(game_t *game, int index)
{
    if (index >= MAX_DUCKS)
        return;
        
    duck_t *duck = &game->ducks[index];
    
    duck->alive = 1;
    duck->animation_frame = 0;
    
    // Random spawn position (left or right side)
    if (rand() % 2 == 0) {
        duck->position.x = -DUCK_SIZE;
        duck->velocity.x = get_random_float(DUCK_SPEED * 0.5f, DUCK_SPEED);
    } else {
        duck->position.x = WINDOW_WIDTH;
        duck->velocity.x = -get_random_float(DUCK_SPEED * 0.5f, DUCK_SPEED);
    }
    
    duck->position.y = get_random_float(100, WINDOW_HEIGHT - DUCK_SIZE - 100);
    duck->velocity.y = get_random_float(-50, 50);
    
    sfSprite_setPosition(duck->sprite, duck->position);
    sfClock_restart(duck->animation_clock);
}

void update_ducks(game_t *game)
{
    float delta_time = sfTime_asSeconds(sfClock_restart(game->game_clock));
    
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (!game->ducks[i].alive)
            continue;
            
        duck_t *duck = &game->ducks[i];
        
        // Update position
        duck->position.x += duck->velocity.x * delta_time;
        duck->position.y += duck->velocity.y * delta_time;
        
        // Bounce off top and bottom
        if (duck->position.y <= 0 || duck->position.y >= WINDOW_HEIGHT - DUCK_SIZE) {
            duck->velocity.y = -duck->velocity.y;
        }
        
        // Remove duck if it goes off screen
        if (duck->position.x < -DUCK_SIZE || duck->position.x > WINDOW_WIDTH) {
            duck->alive = 0;
            // Spawn new duck
            spawn_duck(game, i);
            continue;
        }
        
        // Update sprite position
        sfSprite_setPosition(duck->sprite, duck->position);
        
        // Simple animation (optional)
        if (sfTime_asSeconds(sfClock_getElapsedTime(duck->animation_clock)) > 0.2f) {
            duck->animation_frame = (duck->animation_frame + 1) % 4;
            sfClock_restart(duck->animation_clock);
        }
    }
}

void draw_ducks(game_t *game)
{
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive && game->ducks[i].sprite) {
            sfRenderWindow_drawSprite(game->window, game->ducks[i].sprite, NULL);
        }
    }
}

int check_duck_click(duck_t *duck, sfVector2i mouse_pos)
{
    if (!duck->alive)
        return 0;
        
    sfFloatRect bounds = sfSprite_getGlobalBounds(duck->sprite);
    
    return (mouse_pos.x >= bounds.left && 
            mouse_pos.x <= bounds.left + bounds.width &&
            mouse_pos.y >= bounds.top && 
            mouse_pos.y <= bounds.top + bounds.height);
}