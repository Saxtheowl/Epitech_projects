/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Quest system implementation
*/

#include "../include/my_rpg.h"

void init_quests(game_t *game)
{
    for (int i = 0; i < MAX_QUESTS; i++) {
        game->quests[i].id = -1;
        game->quests[i].active = 0;
        game->quests[i].completed = 0;
    }
    
    game->quests[0].id = 0;
    strcpy(game->quests[0].title, "Goblin Slayer");
    strcpy(game->quests[0].description, "Defeat 3 goblins to protect the village");
    game->quests[0].target_enemy_id = 0;
    game->quests[0].reward_gold = 100;
    game->quests[0].reward_exp = 150;
    
    game->quests[1].id = 1;
    strcpy(game->quests[1].title, "Treasure Hunter");
    strcpy(game->quests[1].description, "Find the ancient treasure hidden in the dungeon");
    game->quests[1].target_item_id = 10;
    game->quests[1].reward_gold = 500;
    game->quests[1].reward_exp = 300;
    
    game->quests[2].id = 2;
    strcpy(game->quests[2].title, "Orc Elimination");
    strcpy(game->quests[2].description, "Clear the orc camp near the forest");
    game->quests[2].target_enemy_id = 5;
    game->quests[2].reward_gold = 200;
    game->quests[2].reward_exp = 250;
}

void start_quest(game_t *game, int quest_id)
{
    if (quest_id < 0 || quest_id >= MAX_QUESTS)
        return;
    
    if (game->quests[quest_id].id == -1)
        return;
    
    game->quests[quest_id].active = 1;
    
    spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
    play_sound(game, 6);
}

void complete_quest(game_t *game, int quest_id)
{
    if (quest_id < 0 || quest_id >= MAX_QUESTS)
        return;
    
    if (!game->quests[quest_id].active || game->quests[quest_id].completed)
        return;
    
    game->quests[quest_id].completed = 1;
    game->quests[quest_id].active = 0;
    
    game->player.stats.gold += game->quests[quest_id].reward_gold;
    player_gain_exp(game, game->quests[quest_id].reward_exp);
    
    spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
    play_sound(game, 7);
}

void check_quest_completion(game_t *game)
{
    for (int i = 0; i < MAX_QUESTS; i++) {
        if (!game->quests[i].active || game->quests[i].completed)
            continue;
        
        if (game->quests[i].target_enemy_id >= 0) {
            int enemies_killed = 0;
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (j >= game->quests[i].target_enemy_id && 
                    j < game->quests[i].target_enemy_id + 3) {
                    if (!game->enemies[j].alive) {
                        enemies_killed++;
                    }
                }
            }
            
            if (enemies_killed >= 3) {
                complete_quest(game, i);
            }
        }
        
        if (game->quests[i].target_item_id >= 0) {
            for (int j = 0; j < game->player.inventory.count; j++) {
                if (game->player.inventory.items[j].id == game->quests[i].target_item_id) {
                    complete_quest(game, i);
                    break;
                }
            }
        }
    }
}