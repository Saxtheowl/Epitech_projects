/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Main screensaver logic functions
*/

#include "my_screensaver.h"

int init_screensaver(screensaver_t *screensaver)
{
    // Initialize structure
    screensaver->window = NULL;
    screensaver->clock = NULL;
    screensaver->current_animation = 1;
    screensaver->elapsed_time = 0.0f;
    screensaver->running = 1;

    // Create window
    if (create_window(screensaver) != 0)
        return -1;

    // Create clock
    screensaver->clock = sfClock_create();
    if (!screensaver->clock)
        return -1;

    // Initialize framebuffer
    if (init_framebuffer(&screensaver->framebuffer, WINDOW_WIDTH, WINDOW_HEIGHT) != 0)
        return -1;

    // Initialize particles
    init_particles(screensaver);

    return 0;
}

void cleanup_screensaver(screensaver_t *screensaver)
{
    if (screensaver->clock)
        sfClock_destroy(screensaver->clock);
    if (screensaver->window)
        sfRenderWindow_destroy(screensaver->window);

    cleanup_framebuffer(&screensaver->framebuffer);
}

int run_screensaver(screensaver_t *screensaver, int animation_id)
{
    animation_func_t animation_func;
    float delta_time;

    screensaver->current_animation = animation_id;
    animation_func = get_animation_function(animation_id);

    if (!animation_func) {
        fprintf(stderr, "Error: Invalid animation ID\n");
        return 84;
    }

    // Main loop
    while (sfRenderWindow_isOpen(screensaver->window) && screensaver->running) {
        // Calculate delta time
        delta_time = sfTime_asSeconds(sfClock_restart(screensaver->clock));
        screensaver->elapsed_time += delta_time;

        // Handle events
        handle_events(screensaver);

        // Update animation
        animation_func(screensaver, delta_time);

        // Render
        render_screensaver(screensaver);
    }

    return 0;
}