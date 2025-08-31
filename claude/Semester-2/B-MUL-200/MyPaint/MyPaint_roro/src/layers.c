/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Layer management system
*/

#include "../include/my_paint.h"

void init_layers(paint_t *paint)
{
    for (int i = 0; i < MAX_LAYERS; i++) {
        paint->layers[i].texture = NULL;
        paint->layers[i].sprite = NULL;
        paint->layers[i].visible = 0;
        paint->layers[i].opacity = 1.0f;
        sprintf(paint->layers[i].name, "Layer %d", i + 1);
    }
    
    paint->layers[0].texture = sfRenderTexture_create(CANVAS_WIDTH, CANVAS_HEIGHT, sfFalse);
    if (paint->layers[0].texture) {
        paint->layers[0].sprite = sfSprite_create();
        if (paint->layers[0].sprite) {
            sfTexture *layer_texture = sfRenderTexture_getTexture(paint->layers[0].texture);
            sfSprite_setTexture(paint->layers[0].sprite, layer_texture, sfFalse);
        }
        paint->layers[0].visible = 1;
        sfRenderTexture_clear(paint->layers[0].texture, sfTransparent);
        sfRenderTexture_display(paint->layers[0].texture);
    }
    
    paint->current_layer = 0;
    paint->layer_count = 1;
}

void add_layer(paint_t *paint)
{
    if (paint->layer_count >= MAX_LAYERS)
        return;
    
    int index = paint->layer_count;
    
    paint->layers[index].texture = sfRenderTexture_create(CANVAS_WIDTH, CANVAS_HEIGHT, sfFalse);
    if (!paint->layers[index].texture)
        return;
    
    paint->layers[index].sprite = sfSprite_create();
    if (!paint->layers[index].sprite) {
        sfRenderTexture_destroy(paint->layers[index].texture);
        paint->layers[index].texture = NULL;
        return;
    }
    
    sfTexture *layer_texture = sfRenderTexture_getTexture(paint->layers[index].texture);
    sfSprite_setTexture(paint->layers[index].sprite, layer_texture, sfFalse);
    
    paint->layers[index].visible = 1;
    paint->layers[index].opacity = 1.0f;
    sprintf(paint->layers[index].name, "Layer %d", index + 1);
    
    sfRenderTexture_clear(paint->layers[index].texture, sfTransparent);
    sfRenderTexture_display(paint->layers[index].texture);
    
    paint->layer_count++;
    paint->current_layer = index;
}

void remove_layer(paint_t *paint, int index)
{
    if (index < 0 || index >= paint->layer_count || paint->layer_count <= 1)
        return;
    
    if (paint->layers[index].texture)
        sfRenderTexture_destroy(paint->layers[index].texture);
    if (paint->layers[index].sprite)
        sfSprite_destroy(paint->layers[index].sprite);
    
    for (int i = index; i < paint->layer_count - 1; i++) {
        paint->layers[i] = paint->layers[i + 1];
    }
    
    paint->layer_count--;
    
    if (paint->current_layer >= paint->layer_count)
        paint->current_layer = paint->layer_count - 1;
    
    paint->layers[paint->layer_count].texture = NULL;
    paint->layers[paint->layer_count].sprite = NULL;
    paint->layers[paint->layer_count].visible = 0;
}

void set_current_layer(paint_t *paint, int index)
{
    if (index >= 0 && index < paint->layer_count) {
        paint->current_layer = index;
    }
}

void merge_layers(paint_t *paint)
{
    if (paint->layer_count <= 1)
        return;
    
    layer_t *base_layer = &paint->layers[0];
    
    if (!base_layer->texture)
        return;
    
    for (int i = 1; i < paint->layer_count; i++) {
        if (paint->layers[i].visible && paint->layers[i].sprite) {
            sfColor sprite_color = sfSprite_getColor(paint->layers[i].sprite);
            sprite_color.a = (unsigned char)(paint->layers[i].opacity * 255);
            sfSprite_setColor(paint->layers[i].sprite, sprite_color);
            
            sfRenderTexture_drawSprite(base_layer->texture, paint->layers[i].sprite, NULL);
        }
    }
    
    sfRenderTexture_display(base_layer->texture);
    
    for (int i = 1; i < paint->layer_count; i++) {
        if (paint->layers[i].texture)
            sfRenderTexture_destroy(paint->layers[i].texture);
        if (paint->layers[i].sprite)
            sfSprite_destroy(paint->layers[i].sprite);
    }
    
    paint->layer_count = 1;
    paint->current_layer = 0;
}