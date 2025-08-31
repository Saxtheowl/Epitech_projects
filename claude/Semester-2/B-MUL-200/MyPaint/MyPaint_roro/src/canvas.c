/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Canvas management and drawing surface
*/

#include "../include/my_paint.h"

void init_canvas(paint_t *paint)
{
    paint->canvas = sfRenderTexture_create(CANVAS_WIDTH, CANVAS_HEIGHT, sfFalse);
    
    if (!paint->canvas)
        return;
    
    paint->canvas_sprite = sfSprite_create();
    if (!paint->canvas_sprite)
        return;
    
    sfTexture *canvas_texture = sfRenderTexture_getTexture(paint->canvas);
    sfSprite_setTexture(paint->canvas_sprite, canvas_texture, sfFalse);
    sfSprite_setPosition(paint->canvas_sprite, (sfVector2f){CANVAS_X, CANVAS_Y});
    
    paint->canvas_view = sfView_create();
    if (paint->canvas_view) {
        sfView_setSize(paint->canvas_view, (sfVector2f){CANVAS_WIDTH, CANVAS_HEIGHT});
        sfView_setCenter(paint->canvas_view, (sfVector2f){CANVAS_WIDTH/2, CANVAS_HEIGHT/2});
    }
    
    clear_canvas(paint);
}

void clear_canvas(paint_t *paint)
{
    if (!paint->canvas)
        return;
    
    sfRenderTexture_clear(paint->canvas, sfWhite);
    sfRenderTexture_display(paint->canvas);
    
    for (int i = 0; i < paint->layer_count; i++) {
        if (paint->layers[i].texture) {
            sfRenderTexture_clear(paint->layers[i].texture, sfTransparent);
            sfRenderTexture_display(paint->layers[i].texture);
        }
    }
}

void resize_canvas(paint_t *paint, int width, int height)
{
    if (paint->canvas) {
        sfRenderTexture_destroy(paint->canvas);
    }
    
    paint->canvas = sfRenderTexture_create(width, height, sfFalse);
    
    if (paint->canvas && paint->canvas_sprite) {
        sfTexture *canvas_texture = sfRenderTexture_getTexture(paint->canvas);
        sfSprite_setTexture(paint->canvas_sprite, canvas_texture, sfFalse);
    }
    
    if (paint->canvas_view) {
        sfView_setSize(paint->canvas_view, (sfVector2f){width, height});
        sfView_setCenter(paint->canvas_view, (sfVector2f){width/2, height/2});
    }
    
    for (int i = 0; i < paint->layer_count; i++) {
        if (paint->layers[i].texture) {
            sfRenderTexture_destroy(paint->layers[i].texture);
            paint->layers[i].texture = sfRenderTexture_create(width, height, sfFalse);
            
            if (paint->layers[i].texture && paint->layers[i].sprite) {
                sfTexture *layer_texture = sfRenderTexture_getTexture(paint->layers[i].texture);
                sfSprite_setTexture(paint->layers[i].sprite, layer_texture, sfFalse);
            }
        }
    }
    
    clear_canvas(paint);
}

sfVector2i canvas_to_world(paint_t *paint, sfVector2i canvas_pos)
{
    sfVector2i world_pos;
    world_pos.x = (int)(canvas_pos.x / paint->zoom_level);
    world_pos.y = (int)(canvas_pos.y / paint->zoom_level);
    return world_pos;
}

sfVector2i world_to_canvas(paint_t *paint, sfVector2i world_pos)
{
    sfVector2i canvas_pos;
    canvas_pos.x = (int)(world_pos.x * paint->zoom_level);
    canvas_pos.y = (int)(world_pos.y * paint->zoom_level);
    return canvas_pos;
}