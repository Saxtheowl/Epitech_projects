/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Tower defense game header
*/

#ifndef MY_DEFENDER_H
#define MY_DEFENDER_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define GRID_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 20

#define CASTLE_HP 100
#define STARTING_MONEY 500

typedef enum scene_e {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_PAUSE,
    SCENE_GAME_OVER,
    SCENE_HOW_TO_PLAY
} scene_t;

typedef enum building_type_e {
    BUILD_NONE,
    BUILD_WALL,
    BUILD_BASIC_TOWER,
    BUILD_SLOW_TOWER,
    BUILD_HEAVY_TOWER,
    BUILD_COUNT
} building_type_t;

typedef enum enemy_type_e {
    ENEMY_BASIC,
    ENEMY_FAST,
    ENEMY_TANK,
    ENEMY_COUNT
} enemy_type_t;

typedef struct building_s {
    building_type_t type;
    sfVector2i pos;
    int hp;
    int damage;
    float range;
    float attack_speed;
    sfClock *attack_clock;
    sfSprite *sprite;
} building_t;

typedef struct enemy_s {
    enemy_type_t type;
    sfVector2f pos;
    sfVector2f target_pos;
    int hp;
    int max_hp;
    float speed;
    int reward;
    sfClock *move_clock;
    sfSprite *sprite;
    struct enemy_s *next;
} enemy_t;

typedef struct bullet_s {
    sfVector2f pos;
    sfVector2f velocity;
    int damage;
    enemy_t *target;
    sfSprite *sprite;
    struct bullet_s *next;
} bullet_t;

typedef struct wave_s {
    int enemy_count;
    enemy_type_t enemy_type;
    float spawn_delay;
    int spawned;
    sfClock *spawn_clock;
} wave_t;

typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfVector2f pos;
    sfVector2f size;
    int is_hovered;
    int is_clicked;
    void (*callback)(void *game);
} button_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfEvent event;
    
    scene_t current_scene;
    
    // Game state
    int castle_hp;
    int money;
    int score;
    int wave_number;
    int enemies_killed;
    
    // Grid and buildings
    building_type_t grid[MAP_HEIGHT][MAP_WIDTH];
    building_t buildings[MAP_HEIGHT * MAP_WIDTH];
    int building_count;
    
    // Entities
    enemy_t *enemies;
    bullet_t *bullets;
    
    // Wave system
    wave_t current_wave;
    sfClock *wave_clock;
    
    // UI
    building_type_t selected_building;
    button_t *buttons;
    int button_count;
    
    // Graphics
    sfTexture *textures[10];
    sfFont *font;
    sfSprite *background;
    
    // Audio
    sfSound *sounds[5];
    sfSoundBuffer *sound_buffers[5];
    sfMusic *background_music;
    
    // Animation
    sfClock *game_clock;
    
} game_t;

// Core functions
int my_defender(void);
game_t *init_game(void);
void destroy_game(game_t *game);
void game_loop(game_t *game);
void handle_events(game_t *game);
void update_game(game_t *game);
void render_game(game_t *game);

// Scene management
void handle_menu_scene(game_t *game);
void handle_game_scene(game_t *game);
void handle_pause_scene(game_t *game);
void render_menu_scene(game_t *game);
void render_game_scene(game_t *game);
void render_pause_scene(game_t *game);

// Building system
void init_building_system(game_t *game);
int place_building(game_t *game, int x, int y, building_type_t type);
void update_buildings(game_t *game);
void render_buildings(game_t *game);
int get_building_cost(building_type_t type);

// Enemy system
void init_enemy_system(game_t *game);
void spawn_enemy(game_t *game, enemy_type_t type);
void update_enemies(game_t *game);
void render_enemies(game_t *game);
void move_enemy(enemy_t *enemy);
enemy_t *get_nearest_enemy(game_t *game, sfVector2f pos, float range);

// Combat system
void update_combat(game_t *game);
void building_attack(game_t *game, building_t *building);
void spawn_bullet(game_t *game, building_t *building, enemy_t *target);
void update_bullets(game_t *game);
void render_bullets(game_t *game);

// Wave system
void init_wave_system(game_t *game);
void update_wave_system(game_t *game);
void start_next_wave(game_t *game);

// UI functions
void init_ui(game_t *game);
void render_ui(game_t *game);
void render_hud(game_t *game);
void render_building_menu(game_t *game);
button_t *create_button(sfVector2f pos, sfVector2f size, char *text, void (*callback)(void *));
void update_buttons(game_t *game);
void render_buttons(game_t *game);

// Button callbacks
void button_start_game(void *game);
void button_quit_game(void *game);
void button_pause_game(void *game);
void button_resume_game(void *game);
void button_main_menu(void *game);
void button_how_to_play(void *game);

// Utilities
sfVector2f world_to_grid(sfVector2f world_pos);
sfVector2f grid_to_world(sfVector2i grid_pos);
float distance(sfVector2f a, sfVector2f b);
int load_assets(game_t *game);
void play_sound(game_t *game, int sound_id);

#endif