/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Header file for my_hunter duck hunt game
*/

#ifndef MY_HUNTER_H
    #define MY_HUNTER_H

    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <math.h>
    #include <string.h>

    #define WINDOW_WIDTH 1200
    #define WINDOW_HEIGHT 800
    #define MAX_DUCKS 5
    #define DUCK_SPEED 200.0f
    #define FRAME_RATE 60
    #define ANIMATION_SPEED 0.1f

    typedef enum {
        DUCK_FLYING,
        DUCK_HIT,
        DUCK_FALLING,
        DUCK_DEAD
    } duck_state_t;

    typedef struct duck_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f position;
        sfVector2f velocity;
        duck_state_t state;
        sfClock *anim_clock;
        int frame;
        int max_frames;
        int alive;
        sfIntRect rect;
    } duck_t;

    typedef struct game_s {
        sfRenderWindow *window;
        sfEvent event;
        sfClock *game_clock;
        duck_t ducks[MAX_DUCKS];
        int active_ducks;
        int score;
        int ammo;
        sfFont *font;
        sfText *score_text;
        sfText *ammo_text;
        sfSprite *background;
        sfTexture *bg_texture;
        sfSprite *crosshair;
        sfTexture *crosshair_texture;
        sfMusic *bg_music;
        sfSound *shoot_sound;
        sfSoundBuffer *shoot_buffer;
        int game_over;
    } game_t;

    int my_hunter(void);
    void print_help(void);
    game_t *init_game(void);
    void cleanup_game(game_t *game);
    void init_ducks(game_t *game);
    void update_ducks(game_t *game);
    void draw_ducks(game_t *game);
    void spawn_duck(game_t *game, int index);
    void handle_events(game_t *game);
    void handle_mouse_click(game_t *game, int x, int y);
    int check_duck_collision(duck_t *duck, int x, int y);
    void update_duck_animation(duck_t *duck);
    void update_hud(game_t *game);
    void draw_hud(game_t *game);
    sfIntRect create_rect(int left, int top, int width, int height);

#endif