/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Main header file for MyWorld terraformer
*/

#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define MAP_MAX_SIZE 100
#define TILE_SIZE 32
#define MAX_TOOLS 10
#define MAX_BUTTONS 20
#define TOOLBAR_HEIGHT 80
#define PI 3.14159265359

typedef enum tool_type_e {
    TOOL_RAISE,
    TOOL_LOWER,
    TOOL_FLATTEN,
    TOOL_SMOOTH,
    TOOL_NOISE,
    TOOL_RESET,
    TOOL_SELECT_TILES,
    TOOL_SELECT_CORNERS,
    TOOL_INCREASE_SIZE,
    TOOL_DECREASE_SIZE
} tool_type_t;

typedef enum button_state_e {
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_CLICKED
} button_state_t;

typedef enum selection_mode_e {
    SELECT_TILES,
    SELECT_CORNERS
} selection_mode_t;

typedef struct vector2_s {
    float x;
    float y;
} vector2_t;

typedef struct vector3_s {
    float x;
    float y;
    float z;
} vector3_t;

typedef struct tile_s {
    vector3_t corners[4];
    float height;
    sfColor color;
    int selected;
    sfTexture *texture;
} tile_t;

typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    vector2_t pos;
    vector2_t size;
    button_state_t state;
    tool_type_t tool;
    char label[32];
    char tooltip[128];
    int active;
} button_t;

typedef struct camera_s {
    vector3_t pos;
    vector3_t target;
    float zoom;
    float rotation_x;
    float rotation_y;
    matrix projection;
} camera_t;

typedef struct map_s {
    tile_t **tiles;
    int width;
    int height;
    char filename[256];
    int modified;
} map_t;

typedef struct ui_s {
    button_t buttons[MAX_BUTTONS];
    int button_count;
    sfFont *font;
    sfText *help_text;
    sfRectangleShape *toolbar;
    sfRectangleShape *size_input_bg;
    sfText *size_input_text;
    char size_input[16];
    int size_input_active;
    int effect_size;
} ui_t;

typedef struct world_s {
    sfRenderWindow *window;
    sfEvent event;
    map_t map;
    ui_t ui;
    camera_t camera;
    tool_type_t current_tool;
    selection_mode_t selection_mode;
    vector2_t mouse_pos;
    vector2_t last_mouse_pos;
    int mouse_pressed;
    sfClock *clock;
    float delta_time;
    int running;
    sfTexture *textures[5];
    sfSound *sounds[5];
} world_t;

typedef struct matrix_s {
    float m[4][4];
} matrix;

world_t *init_world(void);
void destroy_world(world_t *world);
int run_world(world_t *world);

void init_map(world_t *world, int width, int height);
void destroy_map(map_t *map);
void generate_default_map(world_t *world);
void save_map(world_t *world, const char *filename);
int load_map(world_t *world, const char *filename);

void init_ui(world_t *world);
void destroy_ui(ui_t *ui);
void update_ui(world_t *world);
void render_ui(world_t *world);
void create_button(world_t *world, vector2_t pos, vector2_t size, 
                   const char *label, tool_type_t tool);
void update_button_states(world_t *world);
int handle_button_click(world_t *world, vector2_t mouse_pos);

void init_camera(world_t *world);
void update_camera(world_t *world);
vector2_t world_to_screen(world_t *world, vector3_t world_pos);
vector3_t screen_to_world(world_t *world, vector2_t screen_pos);
vector2_t isometric_projection(vector3_t pos);

void handle_events(world_t *world);
void handle_keyboard(world_t *world);
void handle_mouse(world_t *world);
void update_map_selection(world_t *world);

void render_map(world_t *world);
void render_tile(world_t *world, tile_t *tile, int x, int y);
void render_wireframe(world_t *world);

void apply_tool(world_t *world, int x, int y);
void tool_raise(world_t *world, int x, int y);
void tool_lower(world_t *world, int x, int y);
void tool_flatten(world_t *world, int x, int y);
void tool_smooth(world_t *world, int x, int y);
void tool_noise(world_t *world, int x, int y);
void tool_reset(world_t *world, int x, int y);

matrix create_identity_matrix(void);
matrix multiply_matrices(matrix a, matrix b);
vector3_t transform_point(vector3_t point, matrix m);
matrix create_rotation_matrix_x(float angle);
matrix create_rotation_matrix_y(float angle);
matrix create_translation_matrix(vector3_t translation);

float distance_2d(vector2_t a, vector2_t b);
float clamp(float value, float min, float max);
int is_point_in_rect(vector2_t point, vector2_t pos, vector2_t size);
void play_sound_effect(world_t *world, int sound_id);

#endif