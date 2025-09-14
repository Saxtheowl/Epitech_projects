/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation 4: Colorful spiral pattern rotating in the center
*/

#include "my_screensaver.h"

void animation_spiral(screensaver_t *screensaver, float delta_time)
{
    // Clear framebuffer
    clear_framebuffer(&screensaver->framebuffer, sfBlack);
    
    sfVector2i center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    float time = screensaver->elapsed_time;
    
    // Draw multiple spirals
    for (int spiral = 0; spiral < 3; spiral++) {
        float spiral_offset = spiral * 120.0f; // 120 degrees apart
        
        // Draw spiral arms
        for (float angle = 0; angle < 720; angle += 2) {
            float rad = (angle + time * 50 + spiral_offset) * M_PI / 180.0f;
            float radius = angle * 0.3f;
            
            if (radius > 300)
                break;
                
            int x = center.x + (int)(cos(rad) * radius);
            int y = center.y + (int)(sin(rad) * radius);
            
            // Color based on angle and spiral
            float hue = fmod(angle + spiral_offset + time * 100, 360);
            float brightness = 1.0f - (radius / 300.0f) * 0.5f;
            sfColor spiral_color = hsv_to_rgb(hue, 1.0f, brightness);
            
            // Draw point with some thickness
            for (int dx = -2; dx <= 2; dx++) {
                for (int dy = -2; dy <= 2; dy++) {
                    if (dx * dx + dy * dy <= 4) {
                        set_pixel(&screensaver->framebuffer, x + dx, y + dy, spiral_color);
                    }
                }
            }
        }
    }
    
    // Add pulsing center circle
    float pulse = sin(time * 4) * 0.5f + 0.5f;
    int center_radius = (int)(20 + pulse * 10);
    sfColor center_color = hsv_to_rgb(fmod(time * 200, 360), 1.0f, 1.0f);
    
    draw_filled_circle(&screensaver->framebuffer, center, center_radius, center_color);
    
    // Add rotating outer ring
    for (int i = 0; i < 12; i++) {
        float angle = (i * 30 + time * 100) * M_PI / 180.0f;
        int ring_x = center.x + (int)(cos(angle) * 150);
        int ring_y = center.y + (int)(sin(angle) * 150);
        
        sfColor ring_color = hsv_to_rgb(i * 30.0f, 1.0f, 1.0f);
        sfVector2i ring_pos = {ring_x, ring_y};
        
        draw_filled_circle(&screensaver->framebuffer, ring_pos, 8, ring_color);
    }
}