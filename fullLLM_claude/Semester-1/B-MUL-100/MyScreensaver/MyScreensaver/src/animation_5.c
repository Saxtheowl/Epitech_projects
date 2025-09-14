/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation 5: Starry sky animation (stars going in and out and whose speed depends on their size)
*/

#include "my_screensaver.h"

void animation_starfield(screensaver_t *screensaver, float delta_time)
{
    // Clear framebuffer with dark blue background
    sfColor space_color = {5, 5, 15, 255};
    clear_framebuffer(&screensaver->framebuffer, space_color);
    
    sfVector2i center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    
    // Update and draw stars
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particle_t *star = &screensaver->particles[i];
        
        if (!star->active) {
            // Respawn star at center
            star->position.x = center.x;
            star->position.y = center.y;
            
            // Random direction
            float angle = get_random_float(0, 2 * M_PI);
            float speed = get_random_float(10, 200);
            star->velocity.x = cos(angle) * speed;
            star->velocity.y = sin(angle) * speed;
            
            star->radius = get_random_float(1, 4);
            star->life = 1.0f;
            star->fade = get_random_float(0.1f, 0.5f);
            
            // Brighter stars move slower, dimmer stars move faster
            float brightness = 1.0f - (speed - 10) / 190.0f;
            star->color = sfColor_fromRGB(255 * brightness, 255 * brightness, 255);
            
            star->active = 1;
        }
        
        // Move star outward from center
        star->position.x += star->velocity.x * delta_time;
        star->position.y += star->velocity.y * delta_time;
        
        // Calculate distance from center
        float dx = star->position.x - center.x;
        float dy = star->position.y - center.y;
        float distance = sqrt(dx * dx + dy * dy);
        
        // Fade based on distance
        if (distance > 100) {
            star->life -= star->fade * delta_time;
            if (star->life <= 0) {
                star->active = 0;
                continue;
            }
        }
        
        // Remove star if it goes off screen
        if (star->position.x < 0 || star->position.x >= WINDOW_WIDTH ||
            star->position.y < 0 || star->position.y >= WINDOW_HEIGHT) {
            star->active = 0;
            continue;
        }
        
        // Draw star with trail effect
        sfColor star_color = star->color;
        star_color.a = (sfUint8)(star->life * 255);
        
        // Draw star
        sfVector2i star_pos = {(int)star->position.x, (int)star->position.y};
        
        // Larger stars have more glow
        int glow_radius = (int)star->radius;
        for (int r = 0; r <= glow_radius; r++) {
            sfColor glow_color = star_color;
            glow_color.a = (sfUint8)(star_color.a * (1.0f - (float)r / glow_radius));
            
            if (r == 0) {
                set_pixel(&screensaver->framebuffer, star_pos.x, star_pos.y, glow_color);
            } else {
                draw_circle(&screensaver->framebuffer, star_pos, r, glow_color);
            }
        }
        
        // Draw cross pattern for bright stars
        if (star->radius > 2) {
            sfVector2i h_start = {star_pos.x - (int)star->radius, star_pos.y};
            sfVector2i h_end = {star_pos.x + (int)star->radius, star_pos.y};
            sfVector2i v_start = {star_pos.x, star_pos.y - (int)star->radius};
            sfVector2i v_end = {star_pos.x, star_pos.y + (int)star->radius};
            
            draw_line(&screensaver->framebuffer, h_start, h_end, star_color);
            draw_line(&screensaver->framebuffer, v_start, v_end, star_color);
        }
    }
}