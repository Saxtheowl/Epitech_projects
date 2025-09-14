/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Framebuffer management functions for MyScreensaver project
*/

#include "my_screensaver.h"

int init_framebuffer(framebuffer_t *fb, int width, int height)
{
    fb->width = width;
    fb->height = height;
    
    // Allocate pixel data (RGBA format)
    fb->pixels = malloc(width * height * 4);
    if (!fb->pixels)
        return -1;
        
    // Create texture
    fb->texture = sfTexture_create(width, height);
    if (!fb->texture) {
        free(fb->pixels);
        return -1;
    }
    
    // Create sprite
    fb->sprite = sfSprite_create();
    if (!fb->sprite) {
        sfTexture_destroy(fb->texture);
        free(fb->pixels);
        return -1;
    }
    
    sfSprite_setTexture(fb->sprite, fb->texture, sfTrue);
    
    // Initialize with black pixels
    clear_framebuffer(fb, sfBlack);
    
    return 0;
}

void cleanup_framebuffer(framebuffer_t *fb)
{
    if (fb->sprite)
        sfSprite_destroy(fb->sprite);
    if (fb->texture)
        sfTexture_destroy(fb->texture);
    if (fb->pixels)
        free(fb->pixels);
}

void clear_framebuffer(framebuffer_t *fb, sfColor color)
{
    for (int i = 0; i < fb->width * fb->height * 4; i += 4) {
        fb->pixels[i] = color.r;     // Red
        fb->pixels[i + 1] = color.g; // Green
        fb->pixels[i + 2] = color.b; // Blue
        fb->pixels[i + 3] = color.a; // Alpha
    }
}

void set_pixel(framebuffer_t *fb, int x, int y, sfColor color)
{
    if (x < 0 || x >= fb->width || y < 0 || y >= fb->height)
        return;
        
    int index = (y * fb->width + x) * 4;
    fb->pixels[index] = color.r;
    fb->pixels[index + 1] = color.g;
    fb->pixels[index + 2] = color.b;
    fb->pixels[index + 3] = color.a;
}

void update_framebuffer_texture(framebuffer_t *fb)
{
    sfTexture_updateFromPixels(fb->texture, fb->pixels, fb->width, fb->height, 0, 0);
}

void draw_line(framebuffer_t *fb, sfVector2i start, sfVector2i end, sfColor color)
{
    int dx = abs(end.x - start.x);
    int dy = abs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;
    
    int x = start.x;
    int y = start.y;
    
    while (1) {
        set_pixel(fb, x, y, color);
        
        if (x == end.x && y == end.y)
            break;
            
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_circle(framebuffer_t *fb, sfVector2i center, int radius, sfColor color)
{
    int x = radius;
    int y = 0;
    int err = 0;
    
    while (x >= y) {
        set_pixel(fb, center.x + x, center.y + y, color);
        set_pixel(fb, center.x + y, center.y + x, color);
        set_pixel(fb, center.x - y, center.y + x, color);
        set_pixel(fb, center.x - x, center.y + y, color);
        set_pixel(fb, center.x - x, center.y - y, color);
        set_pixel(fb, center.x - y, center.y - x, color);
        set_pixel(fb, center.x + y, center.y - x, color);
        set_pixel(fb, center.x + x, center.y - y, color);
        
        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_filled_circle(framebuffer_t *fb, sfVector2i center, int radius, sfColor color)
{
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                set_pixel(fb, center.x + x, center.y + y, color);
            }
        }
    }
}