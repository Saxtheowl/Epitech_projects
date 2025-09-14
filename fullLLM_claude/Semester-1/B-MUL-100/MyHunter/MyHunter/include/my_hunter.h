/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Header file for MyHunter project
*/

#ifndef MY_HUNTER_H_
    #define MY_HUNTER_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <time.h>

    // Window constants
    #define WINDOW_WIDTH 1200
    #define WINDOW_HEIGHT 800
    #define WINDOW_TITLE "MyHunter - Duck Hunt"

    // Game constants
    #define DUCK_SPEED 200.0f
    #define DUCK_SIZE 64
    #define MAX_DUCKS 5

    // Duck structure
    typedef struct duck_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f position;
        sfVector2f velocity;
        int alive;
        sfClock *animation_clock;
        int animation_frame;
    } duck_t;

    // Game structure
    typedef struct game_s {
        sfRenderWindow *window;
        sfEvent event;
        sfClock *game_clock;
        duck_t ducks[MAX_DUCKS];
        int score;
        int nb_ducks;
        sfText *score_text;
        sfFont *font;
        sfSprite *background_sprite;
        sfTexture *background_texture;
    } game_t;

    // Function prototypes
    // Main game functions
    int game_loop(game_t *game);
    int init_game(game_t *game);
    void cleanup_game(game_t *game);

    // Window functions
    int create_window(game_t *game);
    void handle_events(game_t *game);

    // Duck functions
    int init_ducks(game_t *game);
    void update_ducks(game_t *game);
    void draw_ducks(game_t *game);
    void spawn_duck(game_t *game, int index);
    int check_duck_click(duck_t *duck, sfVector2i mouse_pos);

    // Utility functions
    void display_help(void);
    float get_random_float(float min, float max);
    int parse_arguments(int ac, char **av);

#endif /* MY_HUNTER_H_ */