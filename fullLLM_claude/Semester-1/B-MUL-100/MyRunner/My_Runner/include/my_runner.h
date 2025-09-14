/*
** EPITECH PROJECT, 2024
** MyRunner
** File description:
** Header file for MyRunner project
*/

#ifndef MY_RUNNER_H_
    #define MY_RUNNER_H_

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
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
    #define WINDOW_TITLE "MyRunner - Endless Runner"

    // Game constants
    #define PLAYER_WIDTH 64
    #define PLAYER_HEIGHT 64
    #define PLAYER_SPEED 300.0f
    #define JUMP_FORCE -500.0f
    #define GRAVITY 1200.0f
    #define GROUND_LEVEL 600

    // Map constants
    #define TILE_SIZE 32
    #define MAX_MAP_WIDTH 200
    #define MAX_MAP_HEIGHT 30

    // Parallax layers
    #define PARALLAX_LAYERS 3

    // Enemies
    #define MAX_ENEMIES 10
    #define ENEMY_SPAWN_RATE 0.02f

    // Player structure
    typedef struct player_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfRectangleShape *hitbox;
        sfVector2f position;
        sfVector2f velocity;
        int on_ground;
        int alive;
        sfClock *animation_clock;
        int animation_frame;
        int max_frames;
    } player_t;

    // Enemy structure
    typedef struct enemy_s {
        sfSprite *sprite;
        sfTexture *texture;
        sfRectangleShape *hitbox;
        sfVector2f position;
        sfVector2f velocity;
        int alive;
        int type;
        sfClock *animation_clock;
        int animation_frame;
    } enemy_t;

    // Map tile structure
    typedef struct tile_s {
        int type;
        sfSprite *sprite;
        sfTexture *texture;
        sfVector2f position;
    } tile_t;

    // Map structure
    typedef struct map_s {
        tile_t tiles[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];
        int width;
        int height;
        float scroll_offset;
    } map_t;

    // Parallax layer structure
    typedef struct parallax_layer_s {
        sfSprite *sprite;
        sfTexture *texture;
        float speed;
        float offset;
    } parallax_layer_t;

    // Game structure
    typedef struct game_s {
        sfRenderWindow *window;
        sfEvent event;
        sfClock *game_clock;
        sfClock *delta_clock;
        
        player_t player;
        enemy_t enemies[MAX_ENEMIES];
        map_t map;
        parallax_layer_t parallax[PARALLAX_LAYERS];
        
        sfText *score_text;
        sfText *game_over_text;
        sfFont *font;
        
        sfMusic *background_music;
        sfSound *jump_sound;
        sfSoundBuffer *jump_buffer;
        
        int score;
        int game_over;
        int infinity_mode;
        float camera_speed;
        float elapsed_time;
    } game_t;

    // Function prototypes
    // Main game functions
    int run_game(game_t *game);
    int init_game(game_t *game);
    void cleanup_game(game_t *game);

    // Window functions
    int create_window(game_t *game);
    void handle_events(game_t *game);
    void render_game(game_t *game);

    // Player functions
    int init_player(game_t *game);
    void update_player(game_t *game, float delta_time);
    void draw_player(game_t *game);
    void player_jump(game_t *game);

    // Map functions
    int load_map(game_t *game, const char *filepath);
    void update_map(game_t *game, float delta_time);
    void draw_map(game_t *game);
    int check_collision_with_map(game_t *game, sfVector2f pos);
    int get_tile_type(game_t *game, int x, int y);

    // Physics functions
    void apply_gravity(player_t *player, float delta_time);
    void handle_collisions(game_t *game);
    int check_player_enemy_collision(player_t *player, enemy_t *enemy);

    // Parallax functions
    int init_parallax(game_t *game);
    void update_parallax(game_t *game, float delta_time);
    void draw_parallax(game_t *game);

    // Enemy functions
    int init_enemies(game_t *game);
    void update_enemies(game_t *game, float delta_time);
    void draw_enemies(game_t *game);
    void spawn_enemy(game_t *game);

    // Utility functions
    void display_help(void);
    int parse_arguments(int ac, char **av, char **map_path, int *infinity_mode);
    float get_random_float(float min, float max);

#endif /* MY_RUNNER_H_ */