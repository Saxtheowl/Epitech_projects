/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Utility functions and asset loading
*/

#include "../include/my_paint.h"

color_t create_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    color_t color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

sfColor color_to_sfml(color_t color)
{
    return sfColor_fromRGBA(color.r, color.g, color.b, color.a);
}

color_t sfml_to_color(sfColor sfml_color)
{
    color_t color;
    color.r = sfml_color.r;
    color.g = sfml_color.g;
    color.b = sfml_color.b;
    color.a = sfml_color.a;
    return color;
}

int point_in_rect(sfVector2i point, sfVector2f pos, sfVector2f size)
{
    return (point.x >= pos.x && point.x <= pos.x + size.x &&
            point.y >= pos.y && point.y <= pos.y + size.y);
}

void load_assets(paint_t *paint)
{
    for (int i = 0; i < TOOL_COUNT; i++) {
        paint->tool_icons[i] = NULL;
    }
    
    char font_path[] = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";
    paint->font = sfFont_createFromFile(font_path);
    
    if (!paint->font) {
        char alt_font[] = "/usr/share/fonts/TTF/arial.ttf";
        paint->font = sfFont_createFromFile(alt_font);
    }
    
    if (!paint->font) {
        char sys_font[] = "/System/Library/Fonts/Arial.ttf";
        paint->font = sfFont_createFromFile(sys_font);
    }
    
    if (!paint->font) {
        fprintf(stderr, "Warning: Could not load font, using default\n");
    }
    
    for (int i = 0; i < TOOL_COUNT; i++) {
        paint->tool_icons[i] = sfTexture_create(32, 32);
        if (paint->tool_icons[i]) {
            sfUint8 *pixels = malloc(32 * 32 * 4);
            if (pixels) {
                for (int j = 0; j < 32 * 32 * 4; j += 4) {
                    switch (i) {
                        case TOOL_PENCIL:
                            pixels[j] = 100;
                            pixels[j + 1] = 100;
                            pixels[j + 2] = 100;
                            break;
                        case TOOL_ERASER:
                            pixels[j] = 255;
                            pixels[j + 1] = 200;
                            pixels[j + 2] = 200;
                            break;
                        case TOOL_RECTANGLE:
                            pixels[j] = 0;
                            pixels[j + 1] = 100;
                            pixels[j + 2] = 200;
                            break;
                        case TOOL_CIRCLE:
                            pixels[j] = 100;
                            pixels[j + 1] = 200;
                            pixels[j + 2] = 100;
                            break;
                        case TOOL_SELECTION:
                            pixels[j] = 200;
                            pixels[j + 1] = 200;
                            pixels[j + 2] = 0;
                            break;
                        default:
                            pixels[j] = 128;
                            pixels[j + 1] = 128;
                            pixels[j + 2] = 128;
                            break;
                    }
                    pixels[j + 3] = 255;
                }
                sfTexture_updateFromPixels(paint->tool_icons[i], pixels, 32, 32, 0, 0);
                free(pixels);
            }
        }
    }
}