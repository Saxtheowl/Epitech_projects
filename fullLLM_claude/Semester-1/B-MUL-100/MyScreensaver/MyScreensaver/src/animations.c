/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Animation management functions for MyScreensaver project
*/

#include "my_screensaver.h"

void init_particles(screensaver_t *screensaver)
{
    for (int i = 0; i < MAX_PARTICLES; i++) {
        screensaver->particles[i].position.x = get_random_float(0, WINDOW_WIDTH);
        screensaver->particles[i].position.y = get_random_float(0, WINDOW_HEIGHT);
        screensaver->particles[i].velocity.x = get_random_float(-100, 100);
        screensaver->particles[i].velocity.y = get_random_float(-100, 100);
        screensaver->particles[i].color = hsv_to_rgb(get_random_float(0, 360), 1.0f, 1.0f);
        screensaver->particles[i].radius = get_random_float(2, 8);
        screensaver->particles[i].life = 1.0f;
        screensaver->particles[i].fade = get_random_float(0.5f, 2.0f);
        screensaver->particles[i].active = 1;
    }
}

animation_func_t get_animation_function(int animation_id)
{
    switch (animation_id) {
        case 1: return animation_horizontal_lines;
        case 2: return animation_bouncing_circles;
        case 3: return animation_fading_circles;
        case 4: return animation_spiral;
        case 5: return animation_starfield;
        default: return NULL;
    }
}

const char *get_animation_description(int animation_id)
{
    switch (animation_id) {
        case 1: return "horizontal lines crossing the window at random height.";
        case 2: return "circles moving in the window and bouncing when touches a border.";
        case 3: return "circles appearing and fading out one after the other.";
        case 4: return "colorful spiral pattern rotating in the center.";
        case 5: return "starry sky animation (stars going in and out and whose speed depends on their size).";
        default: return "unknown animation.";
    }
}