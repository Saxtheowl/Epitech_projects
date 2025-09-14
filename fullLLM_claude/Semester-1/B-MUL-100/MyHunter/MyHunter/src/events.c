/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Event handling for MyHunter project
*/

#include "my_hunter.h"

// This file is included for completeness but events are handled in window.c
// Additional event handling functions can be added here if needed

void handle_mouse_events(game_t *game, sfMouseButtonEvent *mouse_event)
{
    if (mouse_event->button != sfMouseLeft)
        return;
        
    sfVector2i mouse_pos = {mouse_event->x, mouse_event->y};
    
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive && 
            check_duck_click(&game->ducks[i], mouse_pos)) {
            game->ducks[i].alive = 0;
            game->score += 10;
            
            // Spawn new duck after a short delay
            spawn_duck(game, i);
            break;
        }
    }
}

void handle_keyboard_events(game_t *game, sfKeyEvent *key_event)
{
    switch (key_event->code) {
        case sfKeyEscape:
            sfRenderWindow_close(game->window);
            break;
        case sfKeyR:
            // Reset game
            game->score = 0;
            for (int i = 0; i < MAX_DUCKS; i++) {
                if (i < 2) {
                    spawn_duck(game, i);
                } else {
                    game->ducks[i].alive = 0;
                }
            }
            break;
        default:
            break;
    }
}