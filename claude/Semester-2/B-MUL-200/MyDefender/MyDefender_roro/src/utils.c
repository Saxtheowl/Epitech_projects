/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Utility functions
*/

#include "../include/my_defender.h"

sfVector2f world_to_grid(sfVector2f world_pos)
{
    return (sfVector2f){
        (int)(world_pos.x / GRID_SIZE),
        (int)(world_pos.y / GRID_SIZE)
    };
}

sfVector2f grid_to_world(sfVector2i grid_pos)
{
    return (sfVector2f){
        grid_pos.x * GRID_SIZE,
        grid_pos.y * GRID_SIZE
    };
}

float distance(sfVector2f a, sfVector2f b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrtf(dx * dx + dy * dy);
}

int load_assets(game_t *game)
{
    for (int i = 0; i < 10; i++) {
        game->textures[i] = NULL;
    }
    
    for (int i = 0; i < 5; i++) {
        game->sounds[i] = NULL;
        game->sound_buffers[i] = NULL;
    }
    
    game->font = NULL;
    game->background = NULL;
    game->background_music = NULL;
    
    char font_path[] = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";
    game->font = sfFont_createFromFile(font_path);
    
    if (!game->font) {
        char alt_font[] = "/usr/share/fonts/TTF/arial.ttf";
        game->font = sfFont_createFromFile(alt_font);
    }
    
    if (!game->font) {
        char sys_font[] = "/System/Library/Fonts/Arial.ttf";
        game->font = sfFont_createFromFile(sys_font);
    }
    
    if (!game->font) {
        fprintf(stderr, "Warning: Could not load font, using default\n");
    }
    
    game->textures[0] = sfTexture_create(GRID_SIZE, GRID_SIZE);
    if (game->textures[0]) {
        sfUint8 *pixels = malloc(GRID_SIZE * GRID_SIZE * 4);
        if (pixels) {
            for (int i = 0; i < GRID_SIZE * GRID_SIZE * 4; i += 4) {
                pixels[i] = 139;     // R
                pixels[i + 1] = 69;  // G
                pixels[i + 2] = 19;  // B
                pixels[i + 3] = 255; // A
            }
            sfTexture_updateFromPixels(game->textures[0], pixels, GRID_SIZE, GRID_SIZE, 0, 0);
            free(pixels);
        }
    }
    
    game->textures[1] = sfTexture_create(GRID_SIZE, GRID_SIZE);
    if (game->textures[1]) {
        sfUint8 *pixels = malloc(GRID_SIZE * GRID_SIZE * 4);
        if (pixels) {
            for (int i = 0; i < GRID_SIZE * GRID_SIZE * 4; i += 4) {
                pixels[i] = 128;     // R
                pixels[i + 1] = 128; // G
                pixels[i + 2] = 128; // B
                pixels[i + 3] = 255; // A
            }
            sfTexture_updateFromPixels(game->textures[1], pixels, GRID_SIZE, GRID_SIZE, 0, 0);
            free(pixels);
        }
    }
    
    game->background_music = sfMusic_createFromFile("assets/music/background.ogg");
    if (!game->background_music) {
        fprintf(stderr, "Warning: Could not load background music\n");
    } else {
        sfMusic_setLoop(game->background_music, sfTrue);
        sfMusic_setVolume(game->background_music, 30);
        sfMusic_play(game->background_music);
    }
    
    return 1;
}

void play_sound(game_t *game, int sound_id)
{
    if (sound_id < 0 || sound_id >= 5)
        return;
    
    if (game->sounds[sound_id]) {
        if (sfSound_getStatus(game->sounds[sound_id]) != sfPlaying) {
            sfSound_play(game->sounds[sound_id]);
        }
    }
}