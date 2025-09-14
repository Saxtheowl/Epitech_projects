/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Header file for MyScreensaver project
*/

#ifndef MY_SCREENSAVER_H_
    #define MY_SCREENSAVER_H_

    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    #include <string.h>
    #include <unistd.h>

    // Window constants
    #define WINDOW_WIDTH 1280
    #define WINDOW_HEIGHT 720
    #define WINDOW_TITLE "MyScreensaver - Graphical Effects"

    // Animation constants
    #define MAX_ANIMATIONS 5
    #define MAX_PARTICLES 100

    // Particle structure for various animations
    typedef struct particle_s {
        sfVector2f position;
        sfVector2f velocity;
        sfColor color;
        float radius;
        float life;
        float fade;
        int active;
    } particle_t;

    // Framebuffer structure
    typedef struct framebuffer_s {
        sfUint8 *pixels;
        sfTexture *texture;
        sfSprite *sprite;
        int width;
        int height;
    } framebuffer_t;

    // Screensaver structure
    typedef struct screensaver_s {
        sfRenderWindow *window;
        sfEvent event;
        sfClock *clock;
        framebuffer_t framebuffer;
        particle_t particles[MAX_PARTICLES];
        int current_animation;
        float elapsed_time;
        int running;
    } screensaver_t;

    // Animation function pointer type
    typedef void (*animation_func_t)(screensaver_t *screensaver, float delta_time);

    // Function prototypes
    // Main functions
    int run_screensaver(screensaver_t *screensaver, int animation_id);
    int init_screensaver(screensaver_t *screensaver);
    void cleanup_screensaver(screensaver_t *screensaver);

    // Window functions
    int create_window(screensaver_t *screensaver);
    void handle_events(screensaver_t *screensaver);
    void render_screensaver(screensaver_t *screensaver);

    // Framebuffer functions
    int init_framebuffer(framebuffer_t *fb, int width, int height);
    void cleanup_framebuffer(framebuffer_t *fb);
    void clear_framebuffer(framebuffer_t *fb, sfColor color);
    void set_pixel(framebuffer_t *fb, int x, int y, sfColor color);
    void update_framebuffer_texture(framebuffer_t *fb);
    void draw_line(framebuffer_t *fb, sfVector2i start, sfVector2i end, sfColor color);
    void draw_circle(framebuffer_t *fb, sfVector2i center, int radius, sfColor color);
    void draw_filled_circle(framebuffer_t *fb, sfVector2i center, int radius, sfColor color);

    // Animation functions
    void init_particles(screensaver_t *screensaver);
    animation_func_t get_animation_function(int animation_id);
    const char *get_animation_description(int animation_id);

    // Individual animations
    void animation_horizontal_lines(screensaver_t *screensaver, float delta_time);
    void animation_bouncing_circles(screensaver_t *screensaver, float delta_time);
    void animation_fading_circles(screensaver_t *screensaver, float delta_time);
    void animation_spiral(screensaver_t *screensaver, float delta_time);
    void animation_starfield(screensaver_t *screensaver, float delta_time);

    // Utility functions
    void display_help(void);
    void display_descriptions(void);
    int parse_arguments(int ac, char **av, int *animation_id, int *show_descriptions);
    float get_random_float(float min, float max);
    sfColor hsv_to_rgb(float h, float s, float v);
    int clamp(int value, int min, int max);

#endif /* MY_SCREENSAVER_H_ */