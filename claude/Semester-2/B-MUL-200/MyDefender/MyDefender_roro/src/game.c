/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Core game logic and initialization
*/

#include "../include/my_defender.h"

int my_defender(void)
{
    game_t *game = init_game();
    
    if (!game)
        return 84;
    
    game_loop(game);
    destroy_game(game);
    return 0;
}

game_t *init_game(void)
{
    game_t *game = malloc(sizeof(game_t));
    
    if (!game)
        return NULL;
    
    game->window = sfRenderWindow_create((sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32}, 
                                        "MyDefender", sfResize | sfClose, NULL);
    if (!game->window) {
        free(game);
        return NULL;
    }
    
    sfRenderWindow_setFramerateLimit(game->window, 60);
    
    game->current_scene = SCENE_MENU;
    game->castle_hp = CASTLE_HP;
    game->money = STARTING_MONEY;
    game->score = 0;
    game->wave_number = 1;
    game->enemies_killed = 0;
    game->selected_building = BUILD_NONE;
    game->building_count = 0;
    game->enemies = NULL;
    game->bullets = NULL;
    game->buttons = NULL;
    game->button_count = 0;
    
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game->grid[i][j] = BUILD_NONE;
        }
    }
    
    game->game_clock = sfClock_create();
    game->wave_clock = sfClock_create();
    
    if (!load_assets(game)) {
        destroy_game(game);
        return NULL;
    }
    
    init_ui(game);
    init_wave_system(game);
    
    return game;
}

void destroy_game(game_t *game)
{
    if (!game)
        return;
    
    if (game->window)
        sfRenderWindow_destroy(game->window);
    
    if (game->game_clock)
        sfClock_destroy(game->game_clock);
        
    if (game->wave_clock)
        sfClock_destroy(game->wave_clock);
    
    for (int i = 0; i < 10; i++) {
        if (game->textures[i])
            sfTexture_destroy(game->textures[i]);
    }
    
    if (game->font)
        sfFont_destroy(game->font);
    
    if (game->background)
        sfSprite_destroy(game->background);
    
    for (int i = 0; i < 5; i++) {
        if (game->sounds[i])
            sfSound_destroy(game->sounds[i]);
        if (game->sound_buffers[i])
            sfSoundBuffer_destroy(game->sound_buffers[i]);
    }
    
    if (game->background_music)
        sfMusic_destroy(game->background_music);
    
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
    
    bullet_t *bullet = game->bullets;
    while (bullet) {
        bullet_t *next = bullet->next;
        if (bullet->sprite)
            sfSprite_destroy(bullet->sprite);
        free(bullet);
        bullet = next;
    }
    
    for (int i = 0; i < game->building_count; i++) {
        if (game->buildings[i].sprite)
            sfSprite_destroy(game->buildings[i].sprite);
        if (game->buildings[i].attack_clock)
            sfClock_destroy(game->buildings[i].attack_clock);
    }
    
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape)
            sfRectangleShape_destroy(game->buttons[i].shape);
        if (game->buttons[i].text)
            sfText_destroy(game->buttons[i].text);
    }
    if (game->buttons)
        free(game->buttons);
    
    free(game);
}

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        handle_events(game);
        update_game(game);
        render_game(game);
    }
}

void handle_events(game_t *game)
{
    while (sfRenderWindow_pollEvent(game->window, &game->event)) {
        if (game->event.type == sfEvtClosed)
            sfRenderWindow_close(game->window);
        
        if (game->event.type == sfEvtKeyPressed) {
            if (game->event.key.code == sfKeyEscape) {
                if (game->current_scene == SCENE_GAME)
                    game->current_scene = SCENE_PAUSE;
                else if (game->current_scene == SCENE_PAUSE)
                    game->current_scene = SCENE_GAME;
            }
        }
        
        switch (game->current_scene) {
            case SCENE_MENU:
                handle_menu_scene(game);
                break;
            case SCENE_GAME:
                handle_game_scene(game);
                break;
            case SCENE_PAUSE:
                handle_pause_scene(game);
                break;
            default:
                break;
        }
    }
}

void update_game(game_t *game)
{
    if (game->current_scene == SCENE_GAME) {
        update_wave_system(game);
        update_enemies(game);
        update_buildings(game);
        update_combat(game);
        update_bullets(game);
        
        if (game->castle_hp <= 0)
            game->current_scene = SCENE_GAME_OVER;
    }
    
    update_buttons(game);
}

void render_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    
    switch (game->current_scene) {
        case SCENE_MENU:
            render_menu_scene(game);
            break;
        case SCENE_GAME:
            render_game_scene(game);
            break;
        case SCENE_PAUSE:
            render_pause_scene(game);
            break;
        case SCENE_GAME_OVER:
            render_menu_scene(game);
            break;
        default:
            break;
    }
    
    sfRenderWindow_display(game->window);
}