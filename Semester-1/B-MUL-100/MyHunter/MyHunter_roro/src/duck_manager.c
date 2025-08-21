/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Duck management and animation
*/

#include "../include/my_hunter.h"

void init_duck(duck_t *duck)
{
    int side = rand() % 2;
    
    duck->alive = 1;
    duck->frame = 0;
    duck->animation_timer = 0.0f;
    
    duck->position.y = 100 + (rand() % (WINDOW_HEIGHT - 200));
    
    if (side == 0) {
        duck->position.x = -64;
        duck->velocity.x = DUCK_SPEED + (rand() % 100);
        duck->velocity.y = (rand() % 100) - 50;
    } else {
        duck->position.x = WINDOW_WIDTH;
        duck->velocity.x = -(DUCK_SPEED + (rand() % 100));
        duck->velocity.y = (rand() % 100) - 50;
    }
    
    duck->rect.left = 0;
    duck->rect.top = 0;
    duck->rect.width = 64;
    duck->rect.height = 64;
}

void spawn_duck(game_t *game)
{
    int i;
    
    for (i = 0; i < MAX_DUCKS; i++) {
        if (!game->ducks[i].alive) {
            init_duck(&game->ducks[i]);
            return;
        }
    }
}

void animate_duck(duck_t *duck, float delta_time)
{
    duck->animation_timer += delta_time;
    
    if (duck->animation_timer >= ANIMATION_SPEED) {
        duck->frame = (duck->frame + 1) % 4;
        duck->rect.left = duck->frame * 64;
        duck->animation_timer = 0.0f;
    }
}

void update_ducks(game_t *game, float delta_time)
{
    int i;
    
    for (i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive) {
            game->ducks[i].position.x += game->ducks[i].velocity.x * delta_time;
            game->ducks[i].position.y += game->ducks[i].velocity.y * delta_time;
            
            animate_duck(&game->ducks[i], delta_time);
            
            if (game->ducks[i].position.x < -100 || 
                game->ducks[i].position.x > WINDOW_WIDTH + 100 ||
                game->ducks[i].position.y < -100 || 
                game->ducks[i].position.y > WINDOW_HEIGHT + 100) {
                game->ducks[i].alive = 0;
            }
        }
    }
}

int check_duck_collision(game_t *game, sfVector2i mouse_pos)
{
    int i;
    sfVector2f duck_pos;
    float distance;
    
    for (i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive) {
            duck_pos = game->ducks[i].position;
            distance = sqrt(pow(mouse_pos.x - duck_pos.x - 32, 2) + 
                          pow(mouse_pos.y - duck_pos.y - 32, 2));
            
            if (distance < 32) {
                game->ducks[i].alive = 0;
                game->stats.score += 10;
                game->stats.ducks_killed++;
                
                if (game->stats.score > game->stats.high_score) {
                    game->stats.high_score = game->stats.score;
                    save_high_score(game);
                }
                
                if (game->stats.ducks_killed % 10 == 0) {
                    game->stats.level++;
                }
                
                return 1;
            }
        }
    }
    
    return 0;
}