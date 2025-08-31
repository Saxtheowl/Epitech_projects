/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Picture editor header
*/

#ifndef MY_PAINT_H
#define MY_PAINT_H

#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600
#define CANVAS_X 200
#define CANVAS_Y 100

#define MENU_HEIGHT 30
#define TOOLBAR_WIDTH 180
#define COLOR_PALETTE_HEIGHT 200

#define MAX_LAYERS 10
#define MAX_FILENAME 256

typedef enum tool_e {
    TOOL_PENCIL,
    TOOL_ERASER,
    TOOL_RECTANGLE,
    TOOL_CIRCLE,
    TOOL_SELECTION,
    TOOL_COUNT
} tool_t;

typedef enum button_state_e {
    BUTTON_IDLE,
    BUTTON_HOVER,
    BUTTON_PRESSED,
    BUTTON_CLICKED
} button_state_t;

typedef enum eraser_shape_e {
    ERASER_CIRCLE,
    ERASER_SQUARE
} eraser_shape_t;

typedef struct color_s {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} color_t;

typedef struct layer_s {
    sfRenderTexture *texture;
    sfSprite *sprite;
    int visible;
    float opacity;
    char name[64];
} layer_t;

typedef struct selection_s {
    int active;
    sfVector2i start;
    sfVector2i end;
    sfTexture *content;
    sfSprite *sprite;
} selection_t;

typedef struct tool_settings_s {
    int pencil_thickness;
    eraser_shape_t eraser_shape;
    int eraser_size;
    color_t current_color;
    int shape_filled;
} tool_settings_t;

typedef struct menu_item_s {
    char *text;
    sfText *sfml_text;
    sfRectangleShape *background;
    button_state_t state;
    int is_dropdown;
    struct menu_item_s *dropdown_items;
    int dropdown_count;
    int dropdown_visible;
    void (*callback)(void *paint);
} menu_item_t;

typedef struct button_s {
    sfRectangleShape *shape;
    sfText *text;
    sfSprite *icon;
    sfVector2f pos;
    sfVector2f size;
    button_state_t state;
    int selected;
    void (*callback)(void *paint);
} button_t;

typedef struct paint_s {
    sfRenderWindow *window;
    sfEvent event;
    
    // Canvas
    sfRenderTexture *canvas;
    sfSprite *canvas_sprite;
    sfView *canvas_view;
    float zoom_level;
    
    // Layers
    layer_t layers[MAX_LAYERS];
    int current_layer;
    int layer_count;
    
    // Tools
    tool_t current_tool;
    tool_settings_t tool_settings;
    int drawing;
    sfVector2i last_mouse_pos;
    
    // Selection
    selection_t selection;
    
    // UI Elements
    menu_item_t *menu_bar;
    int menu_count;
    button_t *toolbar_buttons;
    int toolbar_button_count;
    button_t *color_palette;
    int palette_size;
    
    // Dialogs
    int show_file_dialog;
    int show_help_dialog;
    int show_about_dialog;
    char filename[MAX_FILENAME];
    
    // Resources
    sfFont *font;
    sfTexture *tool_icons[TOOL_COUNT];
    
} paint_t;

// Core functions
int my_paint(void);
paint_t *init_paint(void);
void destroy_paint(paint_t *paint);
void main_loop(paint_t *paint);
void handle_events(paint_t *paint);
void update_paint(paint_t *paint);
void render_paint(paint_t *paint);

// Canvas functions
void init_canvas(paint_t *paint);
void clear_canvas(paint_t *paint);
void resize_canvas(paint_t *paint, int width, int height);
sfVector2i canvas_to_world(paint_t *paint, sfVector2i canvas_pos);
sfVector2i world_to_canvas(paint_t *paint, sfVector2i world_pos);

// Layer management
void init_layers(paint_t *paint);
void add_layer(paint_t *paint);
void remove_layer(paint_t *paint, int index);
void set_current_layer(paint_t *paint, int index);
void merge_layers(paint_t *paint);

// Tool functions
void init_tools(paint_t *paint);
void set_tool(paint_t *paint, tool_t tool);
void use_pencil(paint_t *paint, sfVector2i pos);
void use_eraser(paint_t *paint, sfVector2i pos);
void draw_rectangle(paint_t *paint, sfVector2i start, sfVector2i end);
void draw_circle(paint_t *paint, sfVector2i center, int radius);
void start_selection(paint_t *paint, sfVector2i pos);
void update_selection(paint_t *paint, sfVector2i pos);
void end_selection(paint_t *paint);

// Drawing functions
void draw_line(paint_t *paint, sfVector2i start, sfVector2i end, color_t color, int thickness);
void draw_pixel(paint_t *paint, sfVector2i pos, color_t color);
void draw_circle_pixels(paint_t *paint, sfVector2i center, int radius, color_t color);
void draw_square_pixels(paint_t *paint, sfVector2i center, int size, color_t color);

// UI functions
void init_ui(paint_t *paint);
void render_menu_bar(paint_t *paint);
void render_toolbar(paint_t *paint);
void render_color_palette(paint_t *paint);
void render_tool_settings(paint_t *paint);
void render_status_bar(paint_t *paint);
void handle_menu_click(paint_t *paint, sfVector2i pos);
void handle_toolbar_click(paint_t *paint, sfVector2i pos);
void handle_palette_click(paint_t *paint, sfVector2i pos);

// Button functions
button_t *create_button(sfVector2f pos, sfVector2f size, char *text, void (*callback)(void *));
void update_button_state(button_t *button, sfVector2i mouse_pos, int clicked);
void render_button(paint_t *paint, button_t *button);

// Menu functions
void init_menu_bar(paint_t *paint);
menu_item_t *create_menu_item(char *text, void (*callback)(void *));
void add_dropdown_item(menu_item_t *parent, menu_item_t *item);
void render_dropdown(paint_t *paint, menu_item_t *menu);

// File operations
void new_file(void *paint);
void open_file(void *paint);
void save_file(void *paint);
void save_file_as(void *paint);
int load_image(paint_t *paint, char *filename);
int save_image(paint_t *paint, char *filename);

// Edit operations
void copy_selection(void *paint);
void cut_selection(void *paint);
void paste_selection(void *paint);
void select_pencil_tool(void *paint);
void select_eraser_tool(void *paint);

// Help functions
void show_help(void *paint);
void show_about(void *paint);

// Dialog functions
void render_file_dialog(paint_t *paint);
void render_help_dialog(paint_t *paint);
void render_about_dialog(paint_t *paint);
void handle_dialog_input(paint_t *paint);

// Utility functions
color_t create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
sfColor color_to_sfml(color_t color);
color_t sfml_to_color(sfColor sfml_color);
int point_in_rect(sfVector2i point, sfVector2f pos, sfVector2f size);
void load_assets(paint_t *paint);

#endif