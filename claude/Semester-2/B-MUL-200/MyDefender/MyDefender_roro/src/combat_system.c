/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Combat and projectile system
*/

#include "../include/my_defender.h"

void update_combat(game_t *game)
{
    for (int i = 0; i < game->building_count; i++) {
        building_t *building = &game->buildings[i];
        
        if (building->type != BUILD_WALL && building->damage > 0) {
            float attack_delay = 1.0f / building->attack_speed;
            float elapsed = sfTime_asSeconds(sfClock_getElapsedTime(building->attack_clock));
            
            if (elapsed >= attack_delay) {
                sfVector2f tower_pos = {
                    building->pos.x * GRID_SIZE + GRID_SIZE/2,
                    building->pos.y * GRID_SIZE + GRID_SIZE/2
                };
                
                enemy_t *target = get_nearest_enemy(game, tower_pos, building->range);
                if (target) {
                    spawn_bullet(game, building, target);
                    sfClock_restart(building->attack_clock);
                    play_sound(game, 3);
                }
            }
        }
    }
}

void building_attack(game_t *game, building_t *building)
{
    sfVector2f tower_pos = {
        building->pos.x * GRID_SIZE + GRID_SIZE/2,
        building->pos.y * GRID_SIZE + GRID_SIZE/2
    };
    
    enemy_t *target = get_nearest_enemy(game, tower_pos, building->range);
    if (target) {
        spawn_bullet(game, building, target);
    }
}

void spawn_bullet(game_t *game, building_t *building, enemy_t *target)
{
    bullet_t *bullet = malloc(sizeof(bullet_t));
    if (!bullet)
        return;
    
    bullet->pos = (sfVector2f){
        building->pos.x * GRID_SIZE + GRID_SIZE/2,
        building->pos.y * GRID_SIZE + GRID_SIZE/2
    };
    
    bullet->damage = building->damage;
    bullet->target = target;
    
    sfVector2f target_pos = {
        target->pos.x + GRID_SIZE/2,
        target->pos.y + GRID_SIZE/2
    };
    
    float dx = target_pos.x - bullet->pos.x;
    float dy = target_pos.y - bullet->pos.y;
    float distance = sqrtf(dx * dx + dy * dy);
    
    float speed = 300.0f;
    bullet->velocity.x = (dx / distance) * speed;
    bullet->velocity.y = (dy / distance) * speed;
    
    bullet->sprite = sfSprite_create();
    if (bullet->sprite && game->textures[9]) {
        sfSprite_setTexture(bullet->sprite, game->textures[9], sfFalse);
        sfSprite_setPosition(bullet->sprite, bullet->pos);
    }
    
    bullet->next = game->bullets;
    game->bullets = bullet;
}

void update_bullets(game_t *game)
{
    bullet_t *bullet = game->bullets;
    bullet_t *prev = NULL;
    
    while (bullet) {
        bullet->pos.x += bullet->velocity.x * (1.0f / 60.0f);
        bullet->pos.y += bullet->velocity.y * (1.0f / 60.0f);
        
        if (bullet->sprite) {
            sfSprite_setPosition(bullet->sprite, bullet->pos);
        }
        
        int remove_bullet = 0;
        
        if (bullet->pos.x < -50 || bullet->pos.x > WINDOW_WIDTH + 50 ||
            bullet->pos.y < -50 || bullet->pos.y > WINDOW_HEIGHT + 50) {
            remove_bullet = 1;
        }
        
        if (!remove_bullet && bullet->target) {
            sfVector2f target_pos = {
                bullet->target->pos.x + GRID_SIZE/2,
                bullet->target->pos.y + GRID_SIZE/2
            };
            
            float dist = distance(bullet->pos, target_pos);
            if (dist < 20.0f) {
                bullet->target->hp -= bullet->damage;
                remove_bullet = 1;
            }
        }
        
        if (remove_bullet) {
            if (prev) {
                prev->next = bullet->next;
            } else {
                game->bullets = bullet->next;
            }
            
            bullet_t *to_delete = bullet;
            bullet = bullet->next;
            
            if (to_delete->sprite)
                sfSprite_destroy(to_delete->sprite);
            free(to_delete);
            continue;
        }
        
        prev = bullet;
        bullet = bullet->next;
    }
}

void render_bullets(game_t *game)
{
    bullet_t *bullet = game->bullets;
    
    while (bullet) {
        if (bullet->sprite) {
            sfRenderWindow_drawSprite(game->window, bullet->sprite, NULL);
        } else {
            sfCircleShape *circle = sfCircleShape_create();
            if (circle) {
                sfCircleShape_setRadius(circle, 3);
                sfCircleShape_setOrigin(circle, (sfVector2f){3, 3});
                sfCircleShape_setPosition(circle, bullet->pos);
                sfCircleShape_setFillColor(circle, sfYellow);
                sfRenderWindow_drawCircleShape(game->window, circle, NULL);
                sfCircleShape_destroy(circle);
            }
        }
        
        bullet = bullet->next;
    }
}