/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Header file for MyHunter game
*/

#ifndef MY_HUNTER_H_
    #define MY_HUNTER_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <math.h>

    #define WINDOW_WIDTH 1200
    #define WINDOW_HEIGHT 800
    #define MAX_DUCKS 5
    #define DUCK_SPEED 100.0f
    #define ANIMATION_SPEED 0.1f

typedef struct {
    sfVector2f position;
    sfVector2f velocity;
    int alive;
    int frame;
    float animation_timer;
    sfIntRect rect;
} duck_t;

typedef struct {
    int score;
    int lives;
    int level;
    int ducks_killed;
    int high_score;
} game_stats_t;

typedef struct {
    sfRenderWindow *window;
    sfTexture *duck_texture;
    sfTexture *background_texture;
    sfTexture *crosshair_texture;
    sfSprite *duck_sprite;
    sfSprite *background_sprite;
    sfSprite *crosshair_sprite;
    sfFont *font;
    sfText *score_text;
    sfText *lives_text;
    sfClock *game_clock;
    sfClock *spawn_clock;
    duck_t ducks[MAX_DUCKS];
    game_stats_t stats;
    int running;
} game_t;

/* Core game functions */
int game_init(game_t *game);
void game_loop(game_t *game);
void game_cleanup(game_t *game);
void display_help(void);

/* Game mechanics */
void handle_events(game_t *game);
void update_game(game_t *game);
void render_game(game_t *game);

/* Duck management */
void init_duck(duck_t *duck);
void spawn_duck(game_t *game);
void update_ducks(game_t *game, float delta_time);
void animate_duck(duck_t *duck, float delta_time);
int check_duck_collision(game_t *game, sfVector2i mouse_pos);

/* Utility functions */
float get_delta_time(sfClock *clock);
void load_high_score(game_t *game);
void save_high_score(game_t *game);

#endif /* !MY_HUNTER_H_ */