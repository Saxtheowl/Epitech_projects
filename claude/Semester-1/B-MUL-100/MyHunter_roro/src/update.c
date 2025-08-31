/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Game update and rendering functions
*/

#include "../include/my_hunter.h"

void update_ducks(game_t *game)
{
    int i;
    float dt = 1.0f / FRAME_RATE;

    for (i = 0; i < MAX_DUCKS; i++) {
        if (!game->ducks[i].alive)
            continue;
        if (game->ducks[i].state == DUCK_FLYING) {
            game->ducks[i].position.x += game->ducks[i].velocity.x * dt;
            game->ducks[i].position.y += game->ducks[i].velocity.y * dt;
            if (game->ducks[i].position.x < -64 || 
                game->ducks[i].position.x > WINDOW_WIDTH ||
                game->ducks[i].position.y < -64 || 
                game->ducks[i].position.y > WINDOW_HEIGHT) {
                game->ducks[i].alive = 0;
                game->active_ducks--;
            }
        } else if (game->ducks[i].state == DUCK_FALLING) {
            game->ducks[i].position.y += 300.0f * dt;
            if (game->ducks[i].position.y > WINDOW_HEIGHT) {
                game->ducks[i].alive = 0;
                game->active_ducks--;
            }
        }
        sfSprite_setPosition(game->ducks[i].sprite, game->ducks[i].position);
        update_duck_animation(&game->ducks[i]);
    }
    if (game->active_ducks == 0 && rand() % 60 == 0) {
        for (i = 0; i < MAX_DUCKS; i++) {
            if (!game->ducks[i].alive) {
                spawn_duck(game, i);
                game->active_ducks++;
                break;
            }
        }
    }
}

void draw_ducks(game_t *game)
{
    int i;

    for (i = 0; i < MAX_DUCKS; i++) {
        if (game->ducks[i].alive) {
            sfRenderWindow_drawSprite(game->window, 
                game->ducks[i].sprite, NULL);
        }
    }
}

void update_hud(game_t *game)
{
    char score_str[32];
    char ammo_str[32];

    snprintf(score_str, sizeof(score_str), "Score: %d", game->score);
    snprintf(ammo_str, sizeof(ammo_str), "Ammo: %d", game->ammo);
    sfText_setString(game->score_text, score_str);
    sfText_setString(game->ammo_text, ammo_str);
    if (game->ammo <= 0 && game->active_ducks == 0) {
        game->game_over = 1;
    }
}

void draw_hud(game_t *game)
{
    sfRenderWindow_drawText(game->window, game->score_text, NULL);
    sfRenderWindow_drawText(game->window, game->ammo_text, NULL);
    if (game->game_over) {
        sfText *game_over_text = sfText_create();
        sfText_setFont(game_over_text, game->font);
        sfText_setCharacterSize(game_over_text, 48);
        sfText_setFillColor(game_over_text, sfRed);
        sfText_setString(game_over_text, "GAME OVER");
        sfText_setPosition(game_over_text, 
            (sfVector2f){WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2});
        sfRenderWindow_drawText(game->window, game_over_text, NULL);
        sfText_destroy(game_over_text);
    }
}