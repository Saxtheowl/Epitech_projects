/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Particle system implementation
*/

#include "../include/my_rpg.h"

void init_particles(game_t *game)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        game->particles[i].life = 0.0f;
        game->particles[i].max_life = 0.0f;
        game->particles[i].sprite = sfSprite_create();
        if (game->particles[i].sprite && game->textures[10]) {
            sfSprite_setTexture(game->particles[i].sprite, game->textures[10], sfFalse);
        }
    }
}

void spawn_particle(game_t *game, vector2_t pos, particle_type_t type)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life <= 0.0f) {
            game->particles[i].pos = pos;
            game->particles[i].type = type;
            game->particles[i].max_life = 2.0f;
            game->particles[i].life = game->particles[i].max_life;
            
            game->particles[i].velocity.x = (float)random_int(-20, 20) / 10.0f;
            game->particles[i].velocity.y = (float)random_int(-20, 20) / 10.0f;
            
            switch (type) {
                case PARTICLE_FIRE:
                    game->particles[i].color = sfColor_fromRGB(255, 100, 0);
                    game->particles[i].velocity.y -= 2.0f;
                    break;
                case PARTICLE_MAGIC:
                    game->particles[i].color = sfColor_fromRGB(100, 100, 255);
                    break;
                case PARTICLE_BLOOD:
                    game->particles[i].color = sfColor_fromRGB(150, 0, 0);
                    game->particles[i].velocity.y += 1.0f;
                    break;
                case PARTICLE_SPARKLE:
                    game->particles[i].color = sfColor_fromRGB(255, 255, 100);
                    game->particles[i].max_life = 1.5f;
                    game->particles[i].life = game->particles[i].max_life;
                    break;
                default:
                    game->particles[i].color = sfWhite;
                    break;
            }
            
            break;
        }
    }
}

void update_particles(game_t *game)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0.0f) {
            game->particles[i].life -= 1.0f / 60.0f;
            
            game->particles[i].pos.x += game->particles[i].velocity.x / 60.0f;
            game->particles[i].pos.y += game->particles[i].velocity.y / 60.0f;
            
            game->particles[i].velocity.x *= 0.98f;
            game->particles[i].velocity.y *= 0.98f;
            
            switch (game->particles[i].type) {
                case PARTICLE_FIRE:
                    game->particles[i].velocity.y -= 0.5f / 60.0f;
                    break;
                case PARTICLE_BLOOD:
                    game->particles[i].velocity.y += 2.0f / 60.0f;
                    break;
                default:
                    break;
            }
            
            float life_ratio = game->particles[i].life / game->particles[i].max_life;
            unsigned char alpha = (unsigned char)(life_ratio * 255);
            game->particles[i].color.a = alpha;
        }
    }
}

void render_particles(game_t *game)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (game->particles[i].life > 0.0f && game->particles[i].sprite) {
            sfSprite_setPosition(game->particles[i].sprite, (sfVector2f){
                game->particles[i].pos.x * TILE_SIZE,
                game->particles[i].pos.y * TILE_SIZE
            });
            
            sfSprite_setColor(game->particles[i].sprite, game->particles[i].color);
            
            float scale = game->particles[i].life / game->particles[i].max_life;
            sfSprite_setScale(game->particles[i].sprite, (sfVector2f){scale, scale});
            
            sfRenderWindow_drawSprite(game->window, game->particles[i].sprite, NULL);
        }
    }
}