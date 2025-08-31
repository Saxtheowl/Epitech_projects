/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** File operations for loading and saving images
*/

#include "../include/my_paint.h"

void new_file(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    clear_canvas(paint);
    paint->filename[0] = '\0';
    
    for (int i = 1; i < paint->layer_count; i++) {
        remove_layer(paint, i);
    }
    
    paint->current_layer = 0;
    paint->layer_count = 1;
}

void open_file(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    paint->show_file_dialog = 1;
}

void save_file(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    if (strlen(paint->filename) == 0) {
        save_file_as(data);
        return;
    }
    
    save_image(paint, paint->filename);
}

void save_file_as(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    paint->show_file_dialog = 1;
}

int load_image(paint_t *paint, char *filename)
{
    if (!paint || !filename)
        return 0;
    
    sfTexture *texture = sfTexture_createFromFile(filename, NULL);
    if (!texture)
        return 0;
    
    sfVector2u size = sfTexture_getSize(texture);
    
    if (size.x > 0 && size.y > 0) {
        resize_canvas(paint, size.x, size.y);
        
        if (paint->current_layer < paint->layer_count && 
            paint->layers[paint->current_layer].texture) {
            
            sfSprite *temp_sprite = sfSprite_create();
            if (temp_sprite) {
                sfSprite_setTexture(temp_sprite, texture, sfFalse);
                sfRenderTexture_drawSprite(paint->layers[paint->current_layer].texture, 
                                          temp_sprite, NULL);
                sfRenderTexture_display(paint->layers[paint->current_layer].texture);
                sfSprite_destroy(temp_sprite);
            }
        }
        
        strcpy(paint->filename, filename);
    }
    
    sfTexture_destroy(texture);
    return 1;
}

int save_image(paint_t *paint, char *filename)
{
    if (!paint || !filename)
        return 0;
    
    merge_layers(paint);
    
    if (paint->current_layer >= paint->layer_count || 
        !paint->layers[paint->current_layer].texture)
        return 0;
    
    sfTexture *texture = sfRenderTexture_getTexture(paint->layers[paint->current_layer].texture);
    if (!texture)
        return 0;
    
    sfImage *image = sfTexture_copyToImage(texture);
    if (!image)
        return 0;
    
    char full_filename[MAX_FILENAME];
    strcpy(full_filename, "saves/");
    strcat(full_filename, filename);
    
    if (strstr(filename, ".jpg") == NULL && strstr(filename, ".png") == NULL && 
        strstr(filename, ".bmp") == NULL) {
        strcat(full_filename, ".jpg");
    }
    
    int result = sfImage_saveToFile(image, full_filename);
    sfImage_destroy(image);
    
    if (result) {
        strcpy(paint->filename, filename);
    }
    
    return result;
}