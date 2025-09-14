/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation 3: Circles appearing and fading out one after the other
*/

#include "my_screensaver.h"

static float spawn_timer = 0;

void animation_fading_circles(screensaver_t *screensaver, float delta_time)
{
    spawn_timer += delta_time;
    
    // Clear framebuffer
    clear_framebuffer(&screensaver->framebuffer, sfBlack);
    
    // Spawn new circles periodically
    if (spawn_timer >= 0.3f) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!screensaver->particles[i].active) {
                screensaver->particles[i].position.x = get_random_float(50, WINDOW_WIDTH - 50);
                screensaver->particles[i].position.y = get_random_float(50, WINDOW_HEIGHT - 50);
                screensaver->particles[i].velocity.x = 0;
                screensaver->particles[i].velocity.y = 0;
                screensaver->particles[i].radius = get_random_float(10, 30);
                screensaver->particles[i].life = 1.0f;
                screensaver->particles[i].fade = get_random_float(0.5f, 1.5f);
                screensaver->particles[i].color = hsv_to_rgb(get_random_float(0, 360), 0.8f, 1.0f);
                screensaver->particles[i].active = 1;
                break;
            }
        }
        spawn_timer = 0;
    }
    
    // Update and draw fading circles
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particle_t *circle = &screensaver->particles[i];
        
        if (!circle->active)
            continue;
            
        // Fade out
        circle->life -= circle->fade * delta_time;
        
        if (circle->life <= 0) {
            circle->active = 0;
            continue;
        }
        
        // Scale based on life
        float scale = sin(circle->life * M_PI);
        float current_radius = circle->radius * scale;
        
        // Color with alpha based on life
        sfColor fade_color = circle->color;
        fade_color.a = (sfUint8)(circle->life * 255);
        
        // Draw circle with fade effect
        sfVector2i center = {(int)circle->position.x, (int)circle->position.y};
        
        // Draw multiple circles with different alphas for smooth fade
        for (int ring = 0; ring < 5; ring++) {
            sfColor ring_color = fade_color;
            ring_color.a = (sfUint8)(fade_color.a * (1.0f - ring * 0.2f));
            draw_circle(&screensaver->framebuffer, center, (int)current_radius + ring, ring_color);
        }
        
        // Draw filled center
        draw_filled_circle(&screensaver->framebuffer, center, (int)(current_radius * 0.5f), fade_color);
    }
}