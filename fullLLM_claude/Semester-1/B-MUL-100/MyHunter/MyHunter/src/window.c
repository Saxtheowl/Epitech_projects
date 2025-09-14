/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Window management for MyHunter project
*/

#include "my_hunter.h"

int create_window(game_t *game)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    game->window = sfRenderWindow_create(mode, WINDOW_TITLE, 
                                       sfResize | sfClose, NULL);
    if (!game->window) {
        fprintf(stderr, "Error: Failed to create window\n");
        return 84;
    }
    
    sfRenderWindow_setFramerateLimit(game->window, 60);
    
    return 0;
}

void handle_events(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed) {
            sfRenderWindow_close(game->window);
        }
        
        if (game->event.type == sfEvtKeyPressed) {
            if (game->event.key.code == sfKeyEscape) {
                sfRenderWindow_close(game->window);
            }
        }
        
        if (game->event.type == sfEvtMouseButtonPressed) {
            if (game->event.mouseButton.button == sfMouseLeft) {
                sfVector2i mouse_pos = {game->event.mouseButton.x, 
                                      game->event.mouseButton.y};
                
                // Check if any duck was clicked
                for (int i = 0; i < MAX_DUCKS; i++) {
                    if (game->ducks[i].alive && 
                        check_duck_click(&game->ducks[i], mouse_pos)) {
                        game->ducks[i].alive = 0;
                        game->score += 10;
                        break;
                    }
                }
            }
        }
    }
}