/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Drawing functions and pixel operations
*/

#include "../include/my_paint.h"

void draw_line(paint_t *paint, sfVector2i start, sfVector2i end, color_t color, int thickness)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;
    
    sfVector2i current = start;
    
    while (1) {
        for (int i = -thickness/2; i <= thickness/2; i++) {
            for (int j = -thickness/2; j <= thickness/2; j++) {
                sfVector2i pixel = {current.x + i, current.y + j};
                if (pixel.x >= 0 && pixel.x < CANVAS_WIDTH && 
                    pixel.y >= 0 && pixel.y < CANVAS_HEIGHT) {
                    draw_pixel(paint, pixel, color);
                }
            }
        }
        
        if (current.x == end.x && current.y == end.y)
            break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            current.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            current.y += sy;
        }
    }
    
    sfRenderTexture_display(paint->layers[paint->current_layer].texture);
}

void draw_pixel(paint_t *paint, sfVector2i pos, color_t color)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    if (pos.x < 0 || pos.x >= CANVAS_WIDTH || pos.y < 0 || pos.y >= CANVAS_HEIGHT)
        return;
    
    sfCircleShape *pixel = sfCircleShape_create();
    if (!pixel)
        return;
    
    sfCircleShape_setRadius(pixel, 1);
    sfCircleShape_setPosition(pixel, (sfVector2f){pos.x, pos.y});
    sfCircleShape_setFillColor(pixel, color_to_sfml(color));
    
    sfRenderTexture_drawCircleShape(paint->layers[paint->current_layer].texture, pixel, NULL);
    
    sfCircleShape_destroy(pixel);
}

void draw_circle_pixels(paint_t *paint, sfVector2i center, int radius, color_t color)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                sfVector2i pixel = {center.x + x, center.y + y};
                if (pixel.x >= 0 && pixel.x < CANVAS_WIDTH && 
                    pixel.y >= 0 && pixel.y < CANVAS_HEIGHT) {
                    draw_pixel(paint, pixel, color);
                }
            }
        }
    }
    
    sfRenderTexture_display(paint->layers[paint->current_layer].texture);
}

void draw_square_pixels(paint_t *paint, sfVector2i center, int size, color_t color)
{
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return;
    
    int half_size = size / 2;
    
    for (int y = -half_size; y <= half_size; y++) {
        for (int x = -half_size; x <= half_size; x++) {
            sfVector2i pixel = {center.x + x, center.y + y};
            if (pixel.x >= 0 && pixel.x < CANVAS_WIDTH && 
                pixel.y >= 0 && pixel.y < CANVAS_HEIGHT) {
                draw_pixel(paint, pixel, color);
            }
        }
    }
    
    sfRenderTexture_display(paint->layers[paint->current_layer].texture);
}