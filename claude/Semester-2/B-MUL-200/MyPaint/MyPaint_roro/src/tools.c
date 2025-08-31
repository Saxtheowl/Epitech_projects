/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Drawing tools implementation
*/

#include "../include/my_paint.h"

void init_tools(paint_t *paint)
{
    paint->current_tool = TOOL_PENCIL;
    paint->drawing = 0;
    paint->last_mouse_pos = (sfVector2i){0, 0};
}

void set_tool(paint_t *paint, tool_t tool)
{
    paint->current_tool = tool;
    paint->drawing = 0;
}

void use_pencil(paint_t *paint, sfVector2i pos)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    draw_pixel(paint, pos, paint->tool_settings.current_color);
}

void use_eraser(paint_t *paint, sfVector2i pos)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    color_t eraser_color = create_color(255, 255, 255, 255);
    
    if (paint->tool_settings.eraser_shape == ERASER_CIRCLE) {
        draw_circle_pixels(paint, pos, paint->tool_settings.eraser_size / 2, eraser_color);
    } else {
        draw_square_pixels(paint, pos, paint->tool_settings.eraser_size, eraser_color);
    }
}

void draw_rectangle(paint_t *paint, sfVector2i start, sfVector2i end)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    sfRectangleShape *rect = sfRectangleShape_create();
    if (!rect)
        return;
    
    sfVector2f size = {
        abs(end.x - start.x),
        abs(end.y - start.y)
    };
    
    sfVector2f pos = {
        (start.x < end.x) ? start.x : end.x,
        (start.y < end.y) ? start.y : end.y
    };
    
    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setPosition(rect, pos);
    
    if (paint->tool_settings.shape_filled) {
        sfRectangleShape_setFillColor(rect, color_to_sfml(paint->tool_settings.current_color));
    } else {
        sfRectangleShape_setFillColor(rect, sfTransparent);
        sfRectangleShape_setOutlineThickness(rect, paint->tool_settings.pencil_thickness);
        sfRectangleShape_setOutlineColor(rect, color_to_sfml(paint->tool_settings.current_color));
    }
    
    sfRenderTexture_drawRectangleShape(paint->layers[paint->current_layer].texture, rect, NULL);
    sfRenderTexture_display(paint->layers[paint->current_layer].texture);
    
    sfRectangleShape_destroy(rect);
}

void draw_circle(paint_t *paint, sfVector2i center, int radius)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    sfCircleShape *circle = sfCircleShape_create();
    if (!circle)
        return;
    
    sfCircleShape_setRadius(circle, radius);
    sfCircleShape_setOrigin(circle, (sfVector2f){radius, radius});
    sfCircleShape_setPosition(circle, (sfVector2f){center.x, center.y});
    
    if (paint->tool_settings.shape_filled) {
        sfCircleShape_setFillColor(circle, color_to_sfml(paint->tool_settings.current_color));
    } else {
        sfCircleShape_setFillColor(circle, sfTransparent);
        sfCircleShape_setOutlineThickness(circle, paint->tool_settings.pencil_thickness);
        sfCircleShape_setOutlineColor(circle, color_to_sfml(paint->tool_settings.current_color));
    }
    
    sfRenderTexture_drawCircleShape(paint->layers[paint->current_layer].texture, circle, NULL);
    sfRenderTexture_display(paint->layers[paint->current_layer].texture);
    
    sfCircleShape_destroy(circle);
}

void start_selection(paint_t *paint, sfVector2i pos)
{
    paint->selection.active = 1;
    paint->selection.start = pos;
    paint->selection.end = pos;
}

void update_selection(paint_t *paint, sfVector2i pos)
{
    if (paint->selection.active) {
        paint->selection.end = pos;
    }
}

void end_selection(paint_t *paint)
{
    if (!paint->selection.active)
        return;
    
    int width = abs(paint->selection.end.x - paint->selection.start.x);
    int height = abs(paint->selection.end.y - paint->selection.start.y);
    
    if (width < 2 || height < 2) {
        paint->selection.active = 0;
        return;
    }
    
    if (paint->selection.content) {
        sfTexture_destroy(paint->selection.content);
    }
    
    paint->selection.content = sfTexture_create(width, height);
    
    if (paint->selection.content && paint->current_layer < paint->layer_count &&
        paint->layers[paint->current_layer].texture) {
        
        sfTexture *layer_texture = sfRenderTexture_getTexture(paint->layers[paint->current_layer].texture);
        
        sfIntRect selection_rect = {
            (paint->selection.start.x < paint->selection.end.x) ? 
                paint->selection.start.x : paint->selection.end.x,
            (paint->selection.start.y < paint->selection.end.y) ? 
                paint->selection.start.y : paint->selection.end.y,
            width,
            height
        };
        
        sfTexture_updateFromTexture(paint->selection.content, layer_texture, 
                                   selection_rect.left, selection_rect.top);
        
        if (!paint->selection.sprite) {
            paint->selection.sprite = sfSprite_create();
        }
        
        if (paint->selection.sprite) {
            sfSprite_setTexture(paint->selection.sprite, paint->selection.content, sfFalse);
            sfSprite_setPosition(paint->selection.sprite, (sfVector2f){
                selection_rect.left, selection_rect.top
            });
        }
    }
}