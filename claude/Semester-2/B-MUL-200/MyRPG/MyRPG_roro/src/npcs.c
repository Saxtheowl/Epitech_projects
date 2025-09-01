/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** NPC system implementation
*/

#include "../include/my_rpg.h"

void init_npcs(game_t *game)
{
    for (int i = 0; i < MAX_NPCS; i++) {
        game->npcs[i].id = -1;
        game->npcs[i].sprite = NULL;
        game->npcs[i].has_dialog = 0;
    }
    
    game->npcs[0].id = 0;
    strcpy(game->npcs[0].name, "Village Elder");
    game->npcs[0].pos.x = 5.0f;
    game->npcs[0].pos.y = 5.0f;
    game->npcs[0].has_dialog = 1;
    strcpy(game->npcs[0].dialog, "Welcome to our village, brave adventurer! The goblins have been terrorizing us. Please help!");
    game->npcs[0].quest_id = 0;
    
    game->npcs[1].id = 1;
    strcpy(game->npcs[1].name, "Merchant");
    game->npcs[1].pos.x = 8.0f;
    game->npcs[1].pos.y = 3.0f;
    game->npcs[1].has_dialog = 1;
    strcpy(game->npcs[1].dialog, "I have fine wares for sale! Come back when you have more gold.");
    game->npcs[1].quest_id = -1;
    
    game->npcs[2].id = 2;
    strcpy(game->npcs[2].name, "Treasure Hunter");
    game->npcs[2].pos.x = 12.0f;
    game->npcs[2].pos.y = 8.0f;
    game->npcs[2].has_dialog = 1;
    strcpy(game->npcs[2].dialog, "I've heard tales of ancient treasure hidden deep in the dungeons...");
    game->npcs[2].quest_id = 1;
    
    for (int i = 0; i < 3; i++) {
        if (game->npcs[i].id >= 0) {
            game->npcs[i].sprite = sfSprite_create();
            if (game->npcs[i].sprite && game->textures[3]) {
                sfSprite_setTexture(game->npcs[i].sprite, game->textures[3], sfFalse);
            }
        }
    }
}

void interact_with_npc(game_t *game, int npc_id)
{
    if (npc_id < 0 || npc_id >= MAX_NPCS)
        return;
    
    npc_t *npc = &game->npcs[npc_id];
    
    if (npc->id == -1 || !npc->has_dialog)
        return;
    
    game->dialog_npc = npc;
    game->current_scene = SCENE_DIALOG;
    
    if (npc->quest_id >= 0 && !game->quests[npc->quest_id].active) {
        start_quest(game, npc->quest_id);
    }
    
    play_sound(game, 8);
}

int find_nearby_npc(game_t *game)
{
    for (int i = 0; i < MAX_NPCS; i++) {
        if (game->npcs[i].id >= 0) {
            float dist = distance(game->player.pos, game->npcs[i].pos);
            if (dist < 2.0f) {
                return i;
            }
        }
    }
    return -1;
}

void render_npcs(game_t *game)
{
    for (int i = 0; i < MAX_NPCS; i++) {
        if (game->npcs[i].id >= 0 && game->npcs[i].sprite) {
            sfSprite_setPosition(game->npcs[i].sprite, (sfVector2f){
                game->npcs[i].pos.x * TILE_SIZE - game->camera.x,
                game->npcs[i].pos.y * TILE_SIZE - game->camera.y
            });
            
            sfRenderWindow_drawSprite(game->window, game->npcs[i].sprite, NULL);
        }
    }
}