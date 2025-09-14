/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation 2: Circles moving in the window and bouncing when touches a border
*/

#include "my_screensaver.h"

void animation_bouncing_circles(screensaver_t *screensaver, float delta_time)
{
    // Clear framebuffer
    clear_framebuffer(&screensaver->framebuffer, sfBlack);
    
    // Update and draw bouncing circles
    for (int i = 0; i < 15; i++) {
        particle_t *circle = &screensaver->particles[i];
        
        if (!circle->active)
            continue;
            
        // Update position
        circle->position.x += circle->velocity.x * delta_time;
        circle->position.y += circle->velocity.y * delta_time;
        
        // Bounce off walls
        if (circle->position.x <= circle->radius || circle->position.x >= WINDOW_WIDTH - circle->radius) {
            circle->velocity.x = -circle->velocity.x;
            circle->position.x = clamp(circle->position.x, circle->radius, WINDOW_WIDTH - circle->radius);
        }
        if (circle->position.y <= circle->radius || circle->position.y >= WINDOW_HEIGHT - circle->radius) {
            circle->velocity.y = -circle->velocity.y;
            circle->position.y = clamp(circle->position.y, circle->radius, WINDOW_HEIGHT - circle->radius);
        }
        
        // Change color based on speed
        float speed = sqrt(circle->velocity.x * circle->velocity.x + circle->velocity.y * circle->velocity.y);
        float hue = fmod(speed * 2 + screensaver->elapsed_time * 50, 360);
        circle->color = hsv_to_rgb(hue, 1.0f, 1.0f);
        
        // Draw circle
        sfVector2i center = {(int)circle->position.x, (int)circle->position.y};
        draw_filled_circle(&screensaver->framebuffer, center, (int)circle->radius, circle->color);
        
        // Draw outline
        sfColor outline_color = {255, 255, 255, 150};
        draw_circle(&screensaver->framebuffer, center, (int)circle->radius, outline_color);
    }
}