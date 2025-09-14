/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Window management functions for MyScreensaver project
*/

#include "my_screensaver.h"

int create_window(screensaver_t *screensaver)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    
    screensaver->window = sfRenderWindow_create(mode, WINDOW_TITLE, sfResize | sfClose, NULL);
    if (!screensaver->window)
        return -1;
        
    sfRenderWindow_setFramerateLimit(screensaver->window, 60);
    
    return 0;
}

void handle_events(screensaver_t *screensaver)
{
    while (sfRenderWindow_pollEvent(screensaver->window, &screensaver->event)) {
        switch (screensaver->event.type) {
            case sfEvtClosed:
                sfRenderWindow_close(screensaver->window);
                screensaver->running = 0;
                break;
            case sfEvtKeyPressed:
                switch (screensaver->event.key.code) {
                    case sfKeyEscape:
                        sfRenderWindow_close(screensaver->window);
                        screensaver->running = 0;
                        break;
                    case sfKeyLeft:
                        screensaver->current_animation--;
                        if (screensaver->current_animation < 1)
                            screensaver->current_animation = MAX_ANIMATIONS;
                        init_particles(screensaver); // Reset particles for new animation
                        break;
                    case sfKeyRight:
                        screensaver->current_animation++;
                        if (screensaver->current_animation > MAX_ANIMATIONS)
                            screensaver->current_animation = 1;
                        init_particles(screensaver); // Reset particles for new animation
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void render_screensaver(screensaver_t *screensaver)
{
    // Update framebuffer texture with current pixel data
    update_framebuffer_texture(&screensaver->framebuffer);
    
    // Clear window
    sfRenderWindow_clear(screensaver->window, sfBlack);
    
    // Draw framebuffer sprite
    sfRenderWindow_drawSprite(screensaver->window, screensaver->framebuffer.sprite, NULL);
    
    // Display
    sfRenderWindow_display(screensaver->window);
}