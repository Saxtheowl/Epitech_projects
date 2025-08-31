/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Button callback functions
*/

#include "../include/my_defender.h"

void button_start_game(void *data)
{
    game_t *game = (game_t *)data;
    
    game->current_scene = SCENE_GAME;
    game->castle_hp = CASTLE_HP;
    game->money = STARTING_MONEY;
    game->score = 0;
    game->wave_number = 1;
    game->enemies_killed = 0;
    game->selected_building = BUILD_NONE;
    
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game->grid[i][j] = BUILD_NONE;
        }
    }
    
    enemy_t *enemy = game->enemies;
    while (enemy) {
        enemy_t *next = enemy->next;
        if (enemy->sprite)
            sfSprite_destroy(enemy->sprite);
        if (enemy->move_clock)
            sfClock_destroy(enemy->move_clock);
        free(enemy);
        enemy = next;
    }
    game->enemies = NULL;
    
    bullet_t *bullet = game->bullets;
    while (bullet) {
        bullet_t *next = bullet->next;
        if (bullet->sprite)
            sfSprite_destroy(bullet->sprite);
        free(bullet);
        bullet = next;
    }
    game->bullets = NULL;
    
    game->building_count = 0;
    
    init_wave_system(game);
    
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape)
            sfRectangleShape_destroy(game->buttons[i].shape);
        if (game->buttons[i].text)
            sfText_destroy(game->buttons[i].text);
    }
    game->button_count = 0;
    
    play_sound(game, 0);
}

void button_quit_game(void *data)
{
    game_t *game = (game_t *)data;
    sfRenderWindow_close(game->window);
}

void button_pause_game(void *data)
{
    game_t *game = (game_t *)data;
    game->current_scene = SCENE_PAUSE;
    
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape)
            sfRectangleShape_destroy(game->buttons[i].shape);
        if (game->buttons[i].text)
            sfText_destroy(game->buttons[i].text);
    }
    game->button_count = 0;
    
    init_ui(game);
}

void button_resume_game(void *data)
{
    game_t *game = (game_t *)data;
    game->current_scene = SCENE_GAME;
    
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape)
            sfRectangleShape_destroy(game->buttons[i].shape);
        if (game->buttons[i].text)
            sfText_destroy(game->buttons[i].text);
    }
    game->button_count = 0;
}

void button_main_menu(void *data)
{
    game_t *game = (game_t *)data;
    game->current_scene = SCENE_MENU;
    
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape)
            sfRectangleShape_destroy(game->buttons[i].shape);
        if (game->buttons[i].text)
            sfText_destroy(game->buttons[i].text);
    }
    game->button_count = 0;
    
    init_ui(game);
}

void button_how_to_play(void *data)
{
    game_t *game = (game_t *)data;
    
    game->current_scene = SCENE_HOW_TO_PLAY;
}