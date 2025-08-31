/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Edit operations (copy, cut, paste, tool selection)
*/

#include "../include/my_paint.h"

void copy_selection(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint || !paint->selection.active)
        return;
    
    end_selection(paint);
}

void cut_selection(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint || !paint->selection.active)
        return;
    
    copy_selection(data);
    
    if (paint->current_layer < paint->layer_count && 
        paint->layers[paint->current_layer].texture) {
        
        int width = abs(paint->selection.end.x - paint->selection.start.x);
        int height = abs(paint->selection.end.y - paint->selection.start.y);
        
        sfRectangleShape *clear_rect = sfRectangleShape_create();
        if (clear_rect) {
            sfRectangleShape_setSize(clear_rect, (sfVector2f){width, height});
            sfRectangleShape_setPosition(clear_rect, (sfVector2f){
                (paint->selection.start.x < paint->selection.end.x) ? 
                    paint->selection.start.x : paint->selection.end.x,
                (paint->selection.start.y < paint->selection.end.y) ? 
                    paint->selection.start.y : paint->selection.end.y
            });
            sfRectangleShape_setFillColor(clear_rect, sfWhite);
            
            sfRenderTexture_drawRectangleShape(paint->layers[paint->current_layer].texture, 
                                              clear_rect, NULL);
            sfRenderTexture_display(paint->layers[paint->current_layer].texture);
            
            sfRectangleShape_destroy(clear_rect);
        }
    }
}

void paste_selection(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint || !paint->selection.content || !paint->selection.sprite)
        return;
    
    if (paint->current_layer < paint->layer_count && 
        paint->layers[paint->current_layer].texture) {
        
        sfRenderTexture_drawSprite(paint->layers[paint->current_layer].texture, 
                                  paint->selection.sprite, NULL);
        sfRenderTexture_display(paint->layers[paint->current_layer].texture);
    }
}

void select_pencil_tool(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    set_tool(paint, TOOL_PENCIL);
    
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        paint->toolbar_buttons[i].selected = (i == TOOL_PENCIL);
    }
}

void select_eraser_tool(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    set_tool(paint, TOOL_ERASER);
    
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        paint->toolbar_buttons[i].selected = (i == TOOL_ERASER);
    }
}