/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Core game initialization and main loop
*/

#include "../include/my_rpg.h"

int my_rpg(void)
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
                                        "MyRPG - Fantasy Adventure",
                                        sfResize | sfClose, NULL);
    if (!game->window) {
        free(game);
        return NULL;
    }
    
    sfRenderWindow_setFramerateLimit(game->window, 60);
    
    game->current_scene = SCENE_SPLASH;
    game->previous_scene = SCENE_SPLASH;
    game->game_paused = 0;
    game->combat_enemy = NULL;
    game->dialog_npc = NULL;
    game->dialog_line = 0;
    game->combat_turn = 0;
    
    game->game_clock = sfClock_create();
    game->splash_clock = sfClock_create();
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        game->enemies[i].alive = 0;
        game->enemies[i].ai_clock = sfClock_create();
    }
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        game->particles[i].life = 0.0f;
    }
    
    game->button_count = 0;
    game->buttons = NULL;
    
    load_settings(game);
    load_assets(game);
    init_camera(game);
    init_player(game);
    init_enemies(game);
    init_npcs(game);
    init_quests(game);
    init_particles(game);
    init_ui(game);
    
    load_map(game, "assets/maps/world.map");
    
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
    
    if (game->splash_clock)
        sfClock_destroy(game->splash_clock);
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].ai_clock)
            sfClock_destroy(game->enemies[i].ai_clock);
        if (game->enemies[i].sprite)
            sfSprite_destroy(game->enemies[i].sprite);
    }
    
    for (int i = 0; i < MAX_NPCS; i++) {
        if (game->npcs[i].sprite)
            sfSprite_destroy(game->npcs[i].sprite);
    }
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].sprite)
            sfSprite_destroy(game->particles[i].sprite);
    }
    
    if (game->player.sprite)
        sfSprite_destroy(game->player.sprite);
    
    if (game->player.move_clock)
        sfClock_destroy(game->player.move_clock);
    
    if (game->camera.view)
        sfView_destroy(game->camera.view);
    
    for (int i = 0; i < 256; i++) {
        if (game->tile_sprites[i])
            sfSprite_destroy(game->tile_sprites[i]);
    }
    
    for (int i = 0; i < 50; i++) {
        if (game->textures[i])
            sfTexture_destroy(game->textures[i]);
    }
    
    for (int i = 0; i < 20; i++) {
        if (game->sounds[i])
            sfSound_destroy(game->sounds[i]);
        if (game->sound_buffers[i])
            sfSoundBuffer_destroy(game->sound_buffers[i]);
    }
    
    if (game->background_music)
        sfMusic_destroy(game->background_music);
    
    if (game->font)
        sfFont_destroy(game->font);
    
    if (game->splash_sprite)
        sfSprite_destroy(game->splash_sprite);
    
    if (game->buttons) {
        for (int i = 0; i < game->button_count; i++) {
            if (game->buttons[i].shape)
                sfRectangleShape_destroy(game->buttons[i].shape);
            if (game->buttons[i].text)
                sfText_destroy(game->buttons[i].text);
        }
        free(game->buttons);
    }
    
    if (game->map) {
        for (int i = 0; i < MAP_HEIGHT; i++) {
            free(game->map[i]);
        }
        free(game->map);
    }
    
    free(game);
}

void game_loop(game_t *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        handle_events(game);
        
        if (!game->game_paused) {
            update_game(game);
        }
        
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
                if (game->current_scene == SCENE_GAME) {
                    game->previous_scene = SCENE_GAME;
                    game->current_scene = SCENE_MAIN_MENU;
                } else if (game->current_scene != SCENE_MAIN_MENU) {
                    game->current_scene = game->previous_scene;
                }
            }
        }
        
        switch (game->current_scene) {
            case SCENE_SPLASH:
                handle_splash_scene(game);
                break;
            case SCENE_MAIN_MENU:
                handle_main_menu_scene(game);
                break;
            case SCENE_GAME:
                handle_game_scene(game);
                break;
            case SCENE_INVENTORY:
                handle_inventory_scene(game);
                break;
            case SCENE_SETTINGS:
                handle_settings_scene(game);
                break;
            case SCENE_COMBAT:
                handle_combat_scene(game);
                break;
            case SCENE_DIALOG:
                handle_dialog_scene(game);
                break;
            default:
                break;
        }
    }
}

void update_game(game_t *game)
{
    switch (game->current_scene) {
        case SCENE_SPLASH:
            if (sfTime_asSeconds(sfClock_getElapsedTime(game->splash_clock)) > 3.0f) {
                game->current_scene = SCENE_MAIN_MENU;
            }
            break;
        case SCENE_GAME:
            update_player(game);
            update_enemies(game);
            update_particles(game);
            update_camera(game);
            check_quest_completion(game);
            break;
        case SCENE_COMBAT:
            break;
        default:
            break;
    }
    
    update_buttons(game);
}

void render_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    
    switch (game->current_scene) {
        case SCENE_SPLASH:
            render_splash_scene(game);
            break;
        case SCENE_MAIN_MENU:
            render_main_menu_scene(game);
            break;
        case SCENE_GAME:
            render_game_scene(game);
            break;
        case SCENE_INVENTORY:
            render_inventory_scene(game);
            break;
        case SCENE_SETTINGS:
            render_settings_scene(game);
            break;
        case SCENE_COMBAT:
            render_combat_scene(game);
            break;
        case SCENE_DIALOG:
            render_dialog_scene(game);
            break;
        default:
            break;
    }
    
    sfRenderWindow_display(game->window);
}