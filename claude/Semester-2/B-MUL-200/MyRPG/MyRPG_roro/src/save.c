/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Save and load system implementation
*/

#include "../include/my_rpg.h"

void save_game(game_t *game, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
        return;
    
    save_data_t save_data;
    
    save_data.player = game->player;
    
    for (int i = 0; i < MAX_QUESTS; i++) {
        save_data.quests[i] = game->quests[i];
    }
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        save_data.enemies[i] = game->enemies[i];
    }
    
    save_data.current_scene = game->current_scene;
    save_data.camera = game->camera;
    
    fwrite(&save_data, sizeof(save_data_t), 1, file);
    fclose(file);
    
    spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
}

void load_game(game_t *game, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
        return;
    
    save_data_t save_data;
    
    if (fread(&save_data, sizeof(save_data_t), 1, file) != 1) {
        fclose(file);
        return;
    }
    
    game->player = save_data.player;
    
    for (int i = 0; i < MAX_QUESTS; i++) {
        game->quests[i] = save_data.quests[i];
    }
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        game->enemies[i] = save_data.enemies[i];
        if (game->enemies[i].alive && !game->enemies[i].ai_clock) {
            game->enemies[i].ai_clock = sfClock_create();
        }
    }
    
    game->current_scene = save_data.current_scene;
    game->camera = save_data.camera;
    
    fclose(file);
    
    spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
}

int save_exists(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void create_default_save(game_t *game)
{
    save_game(game, "save.rpg");
}

void auto_save(game_t *game)
{
    static sfClock *auto_save_clock = NULL;
    
    if (!auto_save_clock) {
        auto_save_clock = sfClock_create();
    }
    
    float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(auto_save_clock));
    
    if (elapsed > 60.0f) {
        save_game(game, "autosave.rpg");
        sfClock_restart(auto_save_clock);
    }
}