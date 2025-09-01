/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Role-playing game header
*/

#ifndef MY_RPG_H
#define MY_RPG_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_SIZE 64
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

#define MAX_INVENTORY 20
#define MAX_ENEMIES 50
#define MAX_NPCS 20
#define MAX_QUESTS 10
#define MAX_PARTICLES 200

typedef enum scene_e {
    SCENE_SPLASH,
    SCENE_MAIN_MENU,
    SCENE_GAME,
    SCENE_INVENTORY,
    SCENE_SETTINGS,
    SCENE_GAME_OVER,
    SCENE_COMBAT,
    SCENE_DIALOG
} scene_t;

typedef enum button_state_e {
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_PRESSED
} button_state_t;

typedef enum item_type_e {
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_POTION,
    ITEM_KEY,
    ITEM_TREASURE
} item_type_t;

typedef enum particle_type_e {
    PARTICLE_FIRE,
    PARTICLE_MAGIC,
    PARTICLE_BLOOD,
    PARTICLE_SPARKLE
} particle_type_t;

typedef struct vector2_s {
    float x;
    float y;
} vector2_t;

typedef struct stats_s {
    int level;
    int experience;
    int exp_to_next;
    int health;
    int max_health;
    int mana;
    int max_mana;
    int strength;
    int defense;
    int agility;
    int intelligence;
    int gold;
} stats_t;

typedef struct item_s {
    int id;
    char name[64];
    char description[256];
    item_type_t type;
    int value;
    int stat_bonus;
    sfSprite *sprite;
} item_t;

typedef struct inventory_s {
    item_t items[MAX_INVENTORY];
    int count;
    int equipped_weapon;
    int equipped_armor;
} inventory_t;

typedef struct particle_s {
    vector2_t pos;
    vector2_t velocity;
    sfColor color;
    float life;
    float max_life;
    particle_type_t type;
    sfSprite *sprite;
} particle_t;

typedef struct enemy_s {
    int id;
    char name[64];
    vector2_t pos;
    stats_t stats;
    sfSprite *sprite;
    sfClock *ai_clock;
    int alive;
    int aggressive;
    float detection_range;
} enemy_t;

typedef struct npc_s {
    int id;
    char name[64];
    char dialog[512];
    vector2_t pos;
    sfSprite *sprite;
    int has_quest;
    int quest_id;
} npc_t;

typedef struct quest_s {
    int id;
    char title[128];
    char description[512];
    int completed;
    int active;
    int target_enemy_id;
    int target_item_id;
    int reward_gold;
    int reward_exp;
} quest_t;

typedef struct player_s {
    vector2_t pos;
    vector2_t velocity;
    stats_t stats;
    inventory_t inventory;
    sfSprite *sprite;
    sfClock *move_clock;
    int facing_direction;
} player_t;

typedef struct camera_s {
    sfView *view;
    vector2_t pos;
    float zoom;
    float rotation;
} camera_t;

typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    vector2_t pos;
    vector2_t size;
    button_state_t state;
    void (*callback)(void *rpg);
} button_t;

typedef struct settings_s {
    int window_width;
    int window_height;
    int fullscreen;
    float music_volume;
    float sound_volume;
    int vsync;
} settings_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfEvent event;
    
    scene_t current_scene;
    scene_t previous_scene;
    
    // Game entities
    player_t player;
    enemy_t enemies[MAX_ENEMIES];
    npc_t npcs[MAX_NPCS];
    quest_t quests[MAX_QUESTS];
    particle_t particles[MAX_PARTICLES];
    
    // World
    char **map;
    sfSprite *tile_sprites[256];
    camera_t camera;
    
    // UI
    button_t *buttons;
    int button_count;
    
    // Resources
    sfFont *font;
    sfTexture *textures[50];
    sfMusic *background_music;
    sfSound *sounds[20];
    sfSoundBuffer *sound_buffers[20];
    
    // Game state
    settings_t settings;
    int game_paused;
    sfClock *game_clock;
    
    // Combat
    enemy_t *combat_enemy;
    int combat_turn;
    
    // Dialog
    npc_t *dialog_npc;
    int dialog_line;
    
    // Splash screen
    sfSprite *splash_sprite;
    sfClock *splash_clock;
    
} game_t;

// Core functions
int my_rpg(void);
game_t *init_game(void);
void destroy_game(game_t *game);
void game_loop(game_t *game);
void handle_events(game_t *game);
void update_game(game_t *game);
void render_game(game_t *game);

// Scene management
void handle_splash_scene(game_t *game);
void handle_main_menu_scene(game_t *game);
void handle_game_scene(game_t *game);
void handle_inventory_scene(game_t *game);
void handle_settings_scene(game_t *game);
void handle_combat_scene(game_t *game);
void handle_dialog_scene(game_t *game);

void render_splash_scene(game_t *game);
void render_main_menu_scene(game_t *game);
void render_game_scene(game_t *game);
void render_inventory_scene(game_t *game);
void render_settings_scene(game_t *game);
void render_combat_scene(game_t *game);
void render_dialog_scene(game_t *game);

// Player functions
void init_player(game_t *game);
void update_player(game_t *game);
void move_player(game_t *game, vector2_t direction);
void player_attack(game_t *game, enemy_t *enemy);
void player_level_up(game_t *game);
void player_gain_exp(game_t *game, int exp);

// Enemy functions
void init_enemies(game_t *game);
void update_enemies(game_t *game);
void enemy_ai(game_t *game, enemy_t *enemy);
void enemy_attack(game_t *game, enemy_t *enemy);
int enemy_can_see_player(game_t *game, enemy_t *enemy);

// NPC functions
void init_npcs(game_t *game);
void interact_with_npc(game_t *game, npc_t *npc);
void start_dialog(game_t *game, npc_t *npc);

// Quest system
void init_quests(game_t *game);
void start_quest(game_t *game, int quest_id);
void complete_quest(game_t *game, int quest_id);
void check_quest_completion(game_t *game);

// Inventory system
void init_inventory(game_t *game);
void add_item(game_t *game, item_t item);
void remove_item(game_t *game, int index);
void equip_item(game_t *game, int index);
void use_item(game_t *game, int index);

// Combat system
void init_combat(game_t *game, enemy_t *enemy);
void process_combat_turn(game_t *game);
void end_combat(game_t *game);
int calculate_damage(stats_t *attacker, stats_t *defender);

// Particle system
void init_particles(game_t *game);
void spawn_particle(game_t *game, vector2_t pos, particle_type_t type);
void update_particles(game_t *game);
void render_particles(game_t *game);

// Collision system
int check_collision(vector2_t pos1, vector2_t size1, vector2_t pos2, vector2_t size2);
int check_map_collision(game_t *game, vector2_t pos);
enemy_t *get_enemy_at_pos(game_t *game, vector2_t pos);
npc_t *get_npc_at_pos(game_t *game, vector2_t pos);

// Camera system
void init_camera(game_t *game);
void update_camera(game_t *game);
void camera_follow_player(game_t *game);
void camera_zoom(game_t *game, float factor);

// Map system
void load_map(game_t *game, char *filename);
void render_map(game_t *game);
char get_tile_at(game_t *game, int x, int y);

// UI functions
void init_ui(game_t *game);
void render_hud(game_t *game);
void render_minimap(game_t *game);
button_t *create_button(vector2_t pos, vector2_t size, char *text, void (*callback)(void *));
void update_buttons(game_t *game);
void render_buttons(game_t *game);

// Button callbacks
void button_start_game(void *game);
void button_resume_game(void *game);
void button_settings(void *game);
void button_quit_game(void *game);
void button_back_to_menu(void *game);

// Settings functions
void load_settings(game_t *game);
void save_settings(game_t *game);
void apply_settings(game_t *game);

// Save/Load system
void save_game(game_t *game);
void load_game(game_t *game);

// Asset loading
void load_assets(game_t *game);
void load_textures(game_t *game);
void load_sounds(game_t *game);

// Utility functions
float distance(vector2_t a, vector2_t b);
vector2_t normalize(vector2_t vec);
int random_int(int min, int max);
void play_sound(game_t *game, int sound_id);

#endif