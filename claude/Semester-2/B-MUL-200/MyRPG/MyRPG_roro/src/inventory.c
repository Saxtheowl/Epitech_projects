/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Inventory management system
*/

#include "../include/my_rpg.h"

void init_inventory(game_t *game)
{
    game->player.inventory.count = 0;
    game->player.inventory.equipped_weapon = -1;
    game->player.inventory.equipped_armor = -1;
    
    for (int i = 0; i < MAX_INVENTORY; i++) {
        game->player.inventory.items[i].id = -1;
        game->player.inventory.items[i].sprite = NULL;
    }
    
    item_t sword = {
        .id = 1,
        .type = ITEM_WEAPON,
        .value = 50,
        .stat_bonus = 5,
        .sprite = NULL
    };
    strcpy(sword.name, "Iron Sword");
    strcpy(sword.description, "A sturdy iron sword");
    add_item(game, sword);
    
    item_t potion = {
        .id = 2,
        .type = ITEM_POTION,
        .value = 20,
        .stat_bonus = 25,
        .sprite = NULL
    };
    strcpy(potion.name, "Health Potion");
    strcpy(potion.description, "Restores 25 HP");
    add_item(game, potion);
}

void add_item(game_t *game, item_t item)
{
    if (game->player.inventory.count >= MAX_INVENTORY)
        return;
    
    game->player.inventory.items[game->player.inventory.count] = item;
    game->player.inventory.count++;
}

void remove_item(game_t *game, int index)
{
    if (index < 0 || index >= game->player.inventory.count)
        return;
    
    for (int i = index; i < game->player.inventory.count - 1; i++) {
        game->player.inventory.items[i] = game->player.inventory.items[i + 1];
    }
    
    game->player.inventory.count--;
}

void equip_item(game_t *game, int index)
{
    if (index < 0 || index >= game->player.inventory.count)
        return;
    
    item_t *item = &game->player.inventory.items[index];
    
    switch (item->type) {
        case ITEM_WEAPON:
            game->player.inventory.equipped_weapon = index;
            game->player.stats.strength += item->stat_bonus;
            break;
        case ITEM_ARMOR:
            game->player.inventory.equipped_armor = index;
            game->player.stats.defense += item->stat_bonus;
            break;
        default:
            break;
    }
}

void use_item(game_t *game, int index)
{
    if (index < 0 || index >= game->player.inventory.count)
        return;
    
    item_t *item = &game->player.inventory.items[index];
    
    switch (item->type) {
        case ITEM_POTION:
            game->player.stats.health += item->stat_bonus;
            if (game->player.stats.health > game->player.stats.max_health) {
                game->player.stats.health = game->player.stats.max_health;
            }
            remove_item(game, index);
            spawn_particle(game, game->player.pos, PARTICLE_SPARKLE);
            break;
        case ITEM_WEAPON:
        case ITEM_ARMOR:
            equip_item(game, index);
            break;
        default:
            break;
    }
}