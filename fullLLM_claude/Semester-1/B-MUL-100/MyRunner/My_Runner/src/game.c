/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Main game logic functions for MyRunner project
*/

#include "my_runner.h"

int init_game(game_t *game)
{
    // Initialize game structure
    game->window = NULL;
    game->game_clock = NULL;
    game->delta_clock = NULL;
    game->score_text = NULL;
    game->game_over_text = NULL;
    game->font = NULL;
    game->background_music = NULL;
    game->jump_sound = NULL;
    game->jump_buffer = NULL;
    game->score = 0;
    game->game_over = 0;
    game->infinity_mode = 0;
    game->camera_speed = 200.0f;
    game->elapsed_time = 0.0f;
    
    // Initialize map
    game->map.width = 0;
    game->map.height = 0;
    game->map.scroll_offset = 0.0f;
    
    // Create clocks
    game->game_clock = sfClock_create();
    game->delta_clock = sfClock_create();
    if (!game->game_clock || !game->delta_clock)
        return -1;
    
    // Create window
    if (create_window(game) != 0)
        return -1;
        
    // Load font
    game->font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    if (!game->font) {
        game->font = sfFont_createFromFile("/System/Library/Fonts/Arial.ttf");
        if (!game->font) {
            game->font = sfFont_createFromFile("/usr/share/fonts/TTF/arial.ttf");
        }
    }
    
    // Create text elements
    game->score_text = sfText_create();
    game->game_over_text = sfText_create();
    if (!game->score_text || !game->game_over_text)
        return -1;
        
    if (game->font) {
        sfText_setFont(game->score_text, game->font);
        sfText_setFont(game->game_over_text, game->font);
    }
    
    sfText_setCharacterSize(game->score_text, 24);
    sfText_setFillColor(game->score_text, sfWhite);
    
    sfText_setCharacterSize(game->game_over_text, 48);
    sfText_setFillColor(game->game_over_text, sfRed);
    sfText_setString(game->game_over_text, "GAME OVER");
    
    // Initialize game components
    if (init_player(game) != 0)
        return -1;
    if (init_enemies(game) != 0)
        return -1;
    if (init_parallax(game) != 0)
        return -1;
    
    return 0;
}

void cleanup_game(game_t *game)
{
    // Cleanup player
    if (game->player.sprite)
        sfSprite_destroy(game->player.sprite);
    if (game->player.texture)
        sfTexture_destroy(game->player.texture);
    if (game->player.hitbox)
        sfRectangleShape_destroy(game->player.hitbox);
    if (game->player.animation_clock)
        sfClock_destroy(game->player.animation_clock);
    
    // Cleanup enemies
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].sprite)
            sfSprite_destroy(game->enemies[i].sprite);
        if (game->enemies[i].texture)
            sfTexture_destroy(game->enemies[i].texture);
        if (game->enemies[i].hitbox)
            sfRectangleShape_destroy(game->enemies[i].hitbox);
        if (game->enemies[i].animation_clock)
            sfClock_destroy(game->enemies[i].animation_clock);
    }
    
    // Cleanup map
    for (int y = 0; y < game->map.height; y++) {
        for (int x = 0; x < game->map.width; x++) {
            if (game->map.tiles[y][x].sprite)
                sfSprite_destroy(game->map.tiles[y][x].sprite);
            if (game->map.tiles[y][x].texture)
                sfTexture_destroy(game->map.tiles[y][x].texture);
        }
    }
    
    // Cleanup parallax
    for (int i = 0; i < PARALLAX_LAYERS; i++) {
        if (game->parallax[i].sprite)
            sfSprite_destroy(game->parallax[i].sprite);
        if (game->parallax[i].texture)
            sfTexture_destroy(game->parallax[i].texture);
    }
    
    // Cleanup audio
    if (game->jump_sound)
        sfSound_destroy(game->jump_sound);
    if (game->jump_buffer)
        sfSoundBuffer_destroy(game->jump_buffer);
    if (game->background_music)
        sfMusic_destroy(game->background_music);
    
    // Cleanup other resources
    if (game->score_text)
        sfText_destroy(game->score_text);
    if (game->game_over_text)
        sfText_destroy(game->game_over_text);
    if (game->font)
        sfFont_destroy(game->font);
    if (game->game_clock)
        sfClock_destroy(game->game_clock);
    if (game->delta_clock)
        sfClock_destroy(game->delta_clock);
    if (game->window)
        sfRenderWindow_destroy(game->window);
}

int run_game(game_t *game)
{
    float delta_time;
    char score_str[64];
    
    // Start background music if available
    if (game->background_music) {
        sfMusic_setLoop(game->background_music, sfTrue);
        sfMusic_play(game->background_music);
    }
    
    // Main game loop
    while (sfRenderWindow_isOpen(game->window) && !game->game_over) {
        // Calculate delta time
        delta_time = sfTime_asSeconds(sfClock_restart(game->delta_clock));
        game->elapsed_time += delta_time;
        
        // Handle events
        handle_events(game);
        
        // Update game state
        update_player(game, delta_time);
        update_enemies(game, delta_time);
        update_map(game, delta_time);
        update_parallax(game, delta_time);
        
        // Handle collisions
        handle_collisions(game);
        
        // Update score
        game->score = (int)(game->elapsed_time * 10);
        snprintf(score_str, sizeof(score_str), "Score: %d", game->score);
        sfText_setString(game->score_text, score_str);
        
        // Render game
        render_game(game);
    }
    
    // Game over screen
    if (game->game_over) {
        snprintf(score_str, sizeof(score_str), "Final Score: %d", game->score);
        sfText_setString(game->score_text, score_str);
        
        // Show game over screen for 3 seconds
        sfClock *game_over_clock = sfClock_create();
        while (sfRenderWindow_isOpen(game->window) && 
               sfTime_asSeconds(sfClock_getElapsedTime(game_over_clock)) < 3.0f) {
            handle_events(game);
            render_game(game);
        }
        sfClock_destroy(game_over_clock);
    }
    
    return 0;
}