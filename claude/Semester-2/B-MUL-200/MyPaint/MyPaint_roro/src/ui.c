/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** User interface rendering and management
*/

#include "../include/my_paint.h"

void init_ui(paint_t *paint)
{
    init_menu_bar(paint);
    
    paint->toolbar_button_count = TOOL_COUNT;
    paint->toolbar_buttons = malloc(sizeof(button_t) * paint->toolbar_button_count);
    
    const char *tool_names[TOOL_COUNT] = {"Pencil", "Eraser", "Rectangle", "Circle", "Selection"};
    
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        paint->toolbar_buttons[i] = *create_button(
            (sfVector2f){10, MENU_HEIGHT + 10 + i * 50},
            (sfVector2f){TOOLBAR_WIDTH - 20, 40},
            (char *)tool_names[i],
            NULL
        );
        paint->toolbar_buttons[i].selected = (i == 0);
    }
    
    paint->palette_size = 16;
    paint->color_palette = malloc(sizeof(button_t) * paint->palette_size);
    
    color_t palette_colors[16] = {
        {0, 0, 0, 255}, {255, 255, 255, 255}, {255, 0, 0, 255}, {0, 255, 0, 255},
        {0, 0, 255, 255}, {255, 255, 0, 255}, {255, 0, 255, 255}, {0, 255, 255, 255},
        {128, 128, 128, 255}, {64, 64, 64, 255}, {128, 0, 0, 255}, {0, 128, 0, 255},
        {0, 0, 128, 255}, {128, 128, 0, 255}, {128, 0, 128, 255}, {0, 128, 128, 255}
    };
    
    for (int i = 0; i < paint->palette_size; i++) {
        int row = i / 4;
        int col = i % 4;
        
        paint->color_palette[i] = *create_button(
            (sfVector2f){WINDOW_WIDTH - 180 + col * 40, 
                        MENU_HEIGHT + 50 + row * 40},
            (sfVector2f){35, 35},
            "",
            NULL
        );
        
        if (paint->color_palette[i].shape) {
            sfRectangleShape_setFillColor(paint->color_palette[i].shape, 
                                         color_to_sfml(palette_colors[i]));
        }
    }
}

void render_menu_bar(paint_t *paint)
{
    sfRectangleShape *menu_bg = sfRectangleShape_create();
    if (!menu_bg)
        return;
    
    sfRectangleShape_setSize(menu_bg, (sfVector2f){WINDOW_WIDTH, MENU_HEIGHT});
    sfRectangleShape_setPosition(menu_bg, (sfVector2f){0, 0});
    sfRectangleShape_setFillColor(menu_bg, sfColor_fromRGB(220, 220, 220));
    
    sfRenderWindow_drawRectangleShape(paint->window, menu_bg, NULL);
    sfRectangleShape_destroy(menu_bg);
    
    for (int i = 0; i < paint->menu_count; i++) {
        if (paint->menu_bar[i].background) {
            sfRenderWindow_drawRectangleShape(paint->window, paint->menu_bar[i].background, NULL);
        }
        
        if (paint->menu_bar[i].sfml_text) {
            sfRenderWindow_drawText(paint->window, paint->menu_bar[i].sfml_text, NULL);
        }
        
        if (paint->menu_bar[i].dropdown_visible) {
            render_dropdown(paint, &paint->menu_bar[i]);
        }
    }
}

void render_toolbar(paint_t *paint)
{
    sfRectangleShape *toolbar_bg = sfRectangleShape_create();
    if (!toolbar_bg)
        return;
    
    sfRectangleShape_setSize(toolbar_bg, (sfVector2f){TOOLBAR_WIDTH, WINDOW_HEIGHT - MENU_HEIGHT});
    sfRectangleShape_setPosition(toolbar_bg, (sfVector2f){0, MENU_HEIGHT});
    sfRectangleShape_setFillColor(toolbar_bg, sfColor_fromRGB(240, 240, 240));
    
    sfRenderWindow_drawRectangleShape(paint->window, toolbar_bg, NULL);
    sfRectangleShape_destroy(toolbar_bg);
    
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        render_button(paint, &paint->toolbar_buttons[i]);
    }
}

void render_color_palette(paint_t *paint)
{
    if (!paint->font)
        return;
    
    sfText *title = sfText_create();
    if (title) {
        sfText_setFont(title, paint->font);
        sfText_setString(title, "Colors");
        sfText_setCharacterSize(title, 16);
        sfText_setFillColor(title, sfBlack);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH - 180, MENU_HEIGHT + 20});
        
        sfRenderWindow_drawText(paint->window, title, NULL);
        sfText_destroy(title);
    }
    
    for (int i = 0; i < paint->palette_size; i++) {
        render_button(paint, &paint->color_palette[i]);
    }
}

void render_tool_settings(paint_t *paint)
{
    if (!paint->font)
        return;
    
    int y_offset = MENU_HEIGHT + 300;
    
    sfText *title = sfText_create();
    if (title) {
        sfText_setFont(title, paint->font);
        sfText_setString(title, "Tool Settings");
        sfText_setCharacterSize(title, 16);
        sfText_setFillColor(title, sfBlack);
        sfText_setPosition(title, (sfVector2f){10, y_offset});
        
        sfRenderWindow_drawText(paint->window, title, NULL);
        sfText_destroy(title);
    }
    
    y_offset += 30;
    
    if (paint->current_tool == TOOL_PENCIL) {
        char thickness_str[32];
        sprintf(thickness_str, "Thickness: %d", paint->tool_settings.pencil_thickness);
        
        sfText *thickness_text = sfText_create();
        if (thickness_text) {
            sfText_setFont(thickness_text, paint->font);
            sfText_setString(thickness_text, thickness_str);
            sfText_setCharacterSize(thickness_text, 12);
            sfText_setFillColor(thickness_text, sfBlack);
            sfText_setPosition(thickness_text, (sfVector2f){10, y_offset});
            
            sfRenderWindow_drawText(paint->window, thickness_text, NULL);
            sfText_destroy(thickness_text);
        }
    } else if (paint->current_tool == TOOL_ERASER) {
        char size_str[32];
        sprintf(size_str, "Size: %d", paint->tool_settings.eraser_size);
        
        sfText *size_text = sfText_create();
        if (size_text) {
            sfText_setFont(size_text, paint->font);
            sfText_setString(size_text, size_str);
            sfText_setCharacterSize(size_text, 12);
            sfText_setFillColor(size_text, sfBlack);
            sfText_setPosition(size_text, (sfVector2f){10, y_offset});
            
            sfRenderWindow_drawText(paint->window, size_text, NULL);
            sfText_destroy(size_text);
        }
        
        y_offset += 20;
        
        const char *shape_str = (paint->tool_settings.eraser_shape == ERASER_CIRCLE) ? 
                               "Shape: Circle" : "Shape: Square";
        
        sfText *shape_text = sfText_create();
        if (shape_text) {
            sfText_setFont(shape_text, paint->font);
            sfText_setString(shape_text, shape_str);
            sfText_setCharacterSize(shape_text, 12);
            sfText_setFillColor(shape_text, sfBlack);
            sfText_setPosition(shape_text, (sfVector2f){10, y_offset});
            
            sfRenderWindow_drawText(paint->window, shape_text, NULL);
            sfText_destroy(shape_text);
        }
    }
}

void render_status_bar(paint_t *paint)
{
    if (!paint->font)
        return;
    
    sfRectangleShape *status_bg = sfRectangleShape_create();
    if (status_bg) {
        sfRectangleShape_setSize(status_bg, (sfVector2f){WINDOW_WIDTH, 25});
        sfRectangleShape_setPosition(status_bg, (sfVector2f){0, WINDOW_HEIGHT - 25});
        sfRectangleShape_setFillColor(status_bg, sfColor_fromRGB(200, 200, 200));
        
        sfRenderWindow_drawRectangleShape(paint->window, status_bg, NULL);
        sfRectangleShape_destroy(status_bg);
    }
    
    char status_text[256];
    sprintf(status_text, "Layer: %d/%d | Tool: %s | Zoom: %.0f%%", 
            paint->current_layer + 1, paint->layer_count,
            (paint->current_tool == TOOL_PENCIL) ? "Pencil" :
            (paint->current_tool == TOOL_ERASER) ? "Eraser" :
            (paint->current_tool == TOOL_RECTANGLE) ? "Rectangle" :
            (paint->current_tool == TOOL_CIRCLE) ? "Circle" : "Selection",
            paint->zoom_level * 100);
    
    sfText *status = sfText_create();
    if (status) {
        sfText_setFont(status, paint->font);
        sfText_setString(status, status_text);
        sfText_setCharacterSize(status, 12);
        sfText_setFillColor(status, sfBlack);
        sfText_setPosition(status, (sfVector2f){10, WINDOW_HEIGHT - 20});
        
        sfRenderWindow_drawText(paint->window, status, NULL);
        sfText_destroy(status);
    }
}

void handle_menu_click(paint_t *paint, sfVector2i pos)
{
    for (int i = 0; i < paint->menu_count; i++) {
        if (pos.x >= i * 80 && pos.x < (i + 1) * 80) {
            paint->menu_bar[i].dropdown_visible = !paint->menu_bar[i].dropdown_visible;
            
            for (int j = 0; j < paint->menu_count; j++) {
                if (j != i) {
                    paint->menu_bar[j].dropdown_visible = 0;
                }
            }
            break;
        }
    }
}

void handle_toolbar_click(paint_t *paint, sfVector2i pos)
{
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        if (point_in_rect(pos, paint->toolbar_buttons[i].pos, paint->toolbar_buttons[i].size)) {
            for (int j = 0; j < paint->toolbar_button_count; j++) {
                paint->toolbar_buttons[j].selected = (j == i);
            }
            set_tool(paint, i);
            break;
        }
    }
}

void handle_palette_click(paint_t *paint, sfVector2i pos)
{
    for (int i = 0; i < paint->palette_size; i++) {
        if (point_in_rect(pos, paint->color_palette[i].pos, paint->color_palette[i].size)) {
            sfColor selected_color = sfRectangleShape_getFillColor(paint->color_palette[i].shape);
            paint->tool_settings.current_color = sfml_to_color(selected_color);
            break;
        }
    }
}