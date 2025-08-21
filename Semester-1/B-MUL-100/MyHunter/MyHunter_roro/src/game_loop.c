/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Main game loop and event handling
*/

#include "../include/my_hunter.h"

void handle_events(game_t *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed) {
            game->running = 0;
        }

        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEscape) {
                game->running = 0;
            }
        }

        if (event.type == sfEvtMouseButtonPressed) {
            if (event.mouseButton.button == sfMouseLeft) {
                sfVector2i mouse_pos = {event.mouseButton.x, event.mouseButton.y};
                check_duck_collision(game, mouse_pos);
            }
        }
    }
}

void update_game(game_t *game)
{
    float delta_time = get_delta_time(game->game_clock);
    sfTime spawn_time = sfClock_getElapsedTime(game->spawn_clock);

    if (sfTime_asSeconds(spawn_time) > 2.0f) {
        spawn_duck(game);
        sfClock_restart(game->spawn_clock);
    }

    update_ducks(game, delta_time);

    char score_str[64];
    char lives_str[64];
    sprintf(score_str, "Score: %d (High: %d)", game->stats.score, game->stats.high_score);
    sprintf(lives_str, "Level: %d", game->stats.level);

    sfText_setString(game->score_text, score_str);
    sfText_setString(game->lives_text, lives_str);

    sfText_setPosition(game->score_text, (sfVector2f){10, 10});
    sfText_setPosition(game->lives_text, (sfVector2f){10, 40});
}

void render_game(game_t *game)
{
    int i;
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(game->window);

    sfRenderWindow_clear(game->window, (sfColor){50, 150, 255, 255});

    sfRenderWindow_drawSprite(game->window, game->background_sprite, NULL);

    for (i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive) {
            sfSprite_setPosition(game->duck_sprite, game->ducks[i].position);
            sfSprite_setTextureRect(game->duck_sprite, game->ducks[i].rect);
            sfRenderWindow_drawSprite(game->window, game->duck_sprite, NULL);
        }
    }

    sfSprite_setPosition(game->crosshair_sprite, (sfVector2f){mouse_pos.x - 16, mouse_pos.y - 16});
    sfRenderWindow_drawSprite(game->window, game->crosshair_sprite, NULL);

    sfRenderWindow_drawText(game->window, game->score_text, NULL);
    sfRenderWindow_drawText(game->window, game->lives_text, NULL);

    sfRenderWindow_display(game->window);
}

void game_loop(game_t *game)
{
    while (game->running && sfRenderWindow_isOpen(game->window)) {
        handle_events(game);
        update_game(game);
        render_game(game);
    }
}