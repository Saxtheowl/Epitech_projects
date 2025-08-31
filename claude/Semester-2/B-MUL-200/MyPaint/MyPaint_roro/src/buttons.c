/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Button creation and management
*/

#include "../include/my_paint.h"

button_t *create_button(sfVector2f pos, sfVector2f size, char *text, void (*callback)(void *))
{
    button_t *button = malloc(sizeof(button_t));
    if (!button)
        return NULL;
    
    button->pos = pos;
    button->size = size;
    button->state = BUTTON_IDLE;
    button->selected = 0;
    button->callback = callback;
    
    button->shape = sfRectangleShape_create();
    if (button->shape) {
        sfRectangleShape_setSize(button->shape, size);
        sfRectangleShape_setPosition(button->shape, pos);
        sfRectangleShape_setFillColor(button->shape, sfColor_fromRGB(200, 200, 200));
        sfRectangleShape_setOutlineThickness(button->shape, 1);
        sfRectangleShape_setOutlineColor(button->shape, sfBlack);
    }
    
    button->text = NULL;
    if (text && strlen(text) > 0) {
        button->text = sfText_create();
        if (button->text) {
            sfText_setString(button->text, text);
            sfText_setCharacterSize(button->text, 12);
            sfText_setFillColor(button->text, sfBlack);
            
            sfFloatRect text_bounds = sfText_getLocalBounds(button->text);
            sfText_setPosition(button->text, (sfVector2f){
                pos.x + (size.x - text_bounds.width) / 2,
                pos.y + (size.y - text_bounds.height) / 2
            });
        }
    }
    
    button->icon = NULL;
    
    return button;
}

void update_button_state(button_t *button, sfVector2i mouse_pos, int clicked)
{
    if (!button || !button->shape)
        return;
    
    int is_over = point_in_rect(mouse_pos, button->pos, button->size);
    
    if (clicked && is_over) {
        button->state = BUTTON_CLICKED;
        if (button->callback) {
            button->callback(NULL);
        }
    } else if (is_over) {
        button->state = BUTTON_HOVER;
    } else {
        button->state = BUTTON_IDLE;
    }
    
    sfColor button_color;
    switch (button->state) {
        case BUTTON_CLICKED:
        case BUTTON_PRESSED:
            button_color = sfColor_fromRGB(150, 150, 150);
            break;
        case BUTTON_HOVER:
            button_color = sfColor_fromRGB(220, 220, 220);
            break;
        default:
            button_color = button->selected ? 
                          sfColor_fromRGB(180, 200, 255) : 
                          sfColor_fromRGB(200, 200, 200);
            break;
    }
    
    sfRectangleShape_setFillColor(button->shape, button_color);
}

void render_button(paint_t *paint, button_t *button)
{
    if (!button)
        return;
    
    if (button->shape) {
        sfRenderWindow_drawRectangleShape(paint->window, button->shape, NULL);
    }
    
    if (button->icon) {
        sfRenderWindow_drawSprite(paint->window, button->icon, NULL);
    }
    
    if (button->text && paint->font) {
        sfText_setFont(button->text, paint->font);
        sfRenderWindow_drawText(paint->window, button->text, NULL);
    }
}