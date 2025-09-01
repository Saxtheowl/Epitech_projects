/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Utility functions
*/

#include "../include/my_rpg.h"

float distance(vector2_t a, vector2_t b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

vector2_t normalize(vector2_t v)
{
    float length = sqrt(v.x * v.x + v.y * v.y);
    vector2_t result = {0, 0};
    
    if (length > 0) {
        result.x = v.x / length;
        result.y = v.y / length;
    }
    
    return result;
}

int random_int(int min, int max)
{
    static int seeded = 0;
    
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    if (min > max) {
        int temp = min;
        min = max;
        max = temp;
    }
    
    return min + rand() % (max - min + 1);
}

void play_sound(game_t *game, int sound_id)
{
    if (sound_id < 0 || sound_id >= MAX_SOUNDS || !game->sounds[sound_id])
        return;
    
    sfSound_play(game->sounds[sound_id]);
}

void play_music(game_t *game, int music_id)
{
    if (music_id < 0 || music_id >= MAX_MUSIC || !game->music[music_id])
        return;
    
    for (int i = 0; i < MAX_MUSIC; i++) {
        if (game->music[i] && i != music_id) {
            sfMusic_stop(game->music[i]);
        }
    }
    
    sfMusic_setLoop(game->music[music_id], sfTrue);
    sfMusic_play(game->music[music_id]);
}

sfColor interpolate_color(sfColor a, sfColor b, float t)
{
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    
    sfColor result;
    result.r = (unsigned char)(a.r + (b.r - a.r) * t);
    result.g = (unsigned char)(a.g + (b.g - a.g) * t);
    result.b = (unsigned char)(a.b + (b.b - a.b) * t);
    result.a = (unsigned char)(a.a + (b.a - a.a) * t);
    
    return result;
}

void apply_3d_effect(game_t *game, sfSprite *sprite, float depth)
{
    if (!sprite)
        return;
    
    float scale = 1.0f - (depth * 0.1f);
    if (scale < 0.5f) scale = 0.5f;
    
    sfSprite_setScale(sprite, (sfVector2f){scale, scale});
    
    sfColor color = sfSprite_getColor(sprite);
    unsigned char brightness = (unsigned char)(255 - (depth * 50));
    if (brightness < 100) brightness = 100;
    
    color.r = (color.r * brightness) / 255;
    color.g = (color.g * brightness) / 255;
    color.b = (color.b * brightness) / 255;
    
    sfSprite_setColor(sprite, color);
}

sfVector2f apply_isometric_projection(vector2_t world_pos)
{
    sfVector2f iso_pos;
    
    iso_pos.x = (world_pos.x - world_pos.y) * (TILE_SIZE / 2);
    iso_pos.y = (world_pos.x + world_pos.y) * (TILE_SIZE / 4);
    
    return iso_pos;
}