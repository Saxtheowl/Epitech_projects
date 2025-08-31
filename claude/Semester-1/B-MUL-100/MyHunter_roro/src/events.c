/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Event handling functions
*/

#include "../include/my_hunter.h"

int check_duck_collision(duck_t *duck, int x, int y)
{
    sfFloatRect bounds;

    if (!duck->alive || duck->state != DUCK_FLYING)
        return 0;
    bounds = sfSprite_getGlobalBounds(duck->sprite);
    return (x >= bounds.left && x <= bounds.left + bounds.width &&
            y >= bounds.top && y <= bounds.top + bounds.height);
}

void handle_mouse_click(game_t *game, int x, int y)
{
    int i;
    int hit = 0;

    if (game->ammo <= 0)
        return;
    game->ammo--;
    for (i = 0; i < MAX_DUCKS && !hit; i++) {
        if (check_duck_collision(&game->ducks[i], x, y)) {
            game->ducks[i].state = DUCK_FALLING;
            game->ducks[i].velocity.x = 0;
            game->ducks[i].velocity.y = 0;
            game->score += 100;
            hit = 1;
        }
    }
}

void handle_events(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        switch (game->event.type) {
        case sfEvtClosed:
            sfRenderWindow_close(game->window);
            break;
        case sfEvtKeyPressed:
            if (game->event.key.code == sfKeyEscape) {
                sfRenderWindow_close(game->window);
            }
            break;
        case sfEvtMouseButtonPressed:
            if (game->event.mouseButton.button == sfMouseLeft) {
                handle_mouse_click(game, 
                    game->event.mouseButton.x,
                    game->event.mouseButton.y);
            }
            break;
        default:
            break;
        }
    }
}