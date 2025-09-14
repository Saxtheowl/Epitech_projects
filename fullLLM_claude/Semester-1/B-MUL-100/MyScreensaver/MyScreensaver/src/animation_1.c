/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation 1: Horizontal lines crossing the window at random height
*/

#include "my_screensaver.h"

static float line_positions[10];
static sfColor line_colors[10];
static float line_speeds[10];
static int initialized = 0;

void animation_horizontal_lines(screensaver_t *screensaver, float delta_time)
{
    // Initialize lines on first call
    if (!initialized) {
        for (int i = 0; i < 10; i++) {
            line_positions[i] = get_random_float(-50, WINDOW_WIDTH + 50);
            line_colors[i] = hsv_to_rgb(get_random_float(0, 360), 0.8f, 1.0f);
            line_speeds[i] = get_random_float(50, 200);
        }
        initialized = 1;
    }
    
    // Clear framebuffer
    clear_framebuffer(&screensaver->framebuffer, sfBlack);
    
    // Update and draw lines
    for (int i = 0; i < 10; i++) {
        // Move line
        line_positions[i] += line_speeds[i] * delta_time;
        
        // Reset line if it goes off screen
        if (line_positions[i] > WINDOW_WIDTH + 50) {
            line_positions[i] = -50;
            line_colors[i] = hsv_to_rgb(get_random_float(0, 360), 0.8f, 1.0f);
            line_speeds[i] = get_random_float(50, 200);
        }
        
        // Draw horizontal line at random height
        int y = (int)get_random_float(50, WINDOW_HEIGHT - 50);
        sfVector2i start = {(int)line_positions[i], y};
        sfVector2i end = {(int)line_positions[i] + 100, y};
        
        draw_line(&screensaver->framebuffer, start, end, line_colors[i]);
        
        // Draw some thickness
        for (int thick = 1; thick <= 3; thick++) {
            if (y - thick >= 0) {
                sfVector2i start_thick = {(int)line_positions[i], y - thick};
                sfVector2i end_thick = {(int)line_positions[i] + 100, y - thick};
                draw_line(&screensaver->framebuffer, start_thick, end_thick, line_colors[i]);
            }
            if (y + thick < WINDOW_HEIGHT) {
                sfVector2i start_thick = {(int)line_positions[i], y + thick};
                sfVector2i end_thick = {(int)line_positions[i] + 100, y + thick};
                draw_line(&screensaver->framebuffer, start_thick, end_thick, line_colors[i]);
            }
        }
    }
}