/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Menu system implementation
*/

#include "../include/my_paint.h"

void init_menu_bar(paint_t *paint)
{
    paint->menu_count = 3;
    paint->menu_bar = malloc(sizeof(menu_item_t) * paint->menu_count);
    
    if (!paint->menu_bar)
        return;
    
    paint->menu_bar[0] = *create_menu_item("File", NULL);
    paint->menu_bar[1] = *create_menu_item("Edit", NULL);
    paint->menu_bar[2] = *create_menu_item("Help", NULL);
    
    add_dropdown_item(&paint->menu_bar[0], create_menu_item("New", new_file));
    add_dropdown_item(&paint->menu_bar[0], create_menu_item("Open", open_file));
    add_dropdown_item(&paint->menu_bar[0], create_menu_item("Save", save_file));
    add_dropdown_item(&paint->menu_bar[0], create_menu_item("Save As", save_file_as));
    
    add_dropdown_item(&paint->menu_bar[1], create_menu_item("Pencil", select_pencil_tool));
    add_dropdown_item(&paint->menu_bar[1], create_menu_item("Eraser", select_eraser_tool));
    add_dropdown_item(&paint->menu_bar[1], create_menu_item("Copy", copy_selection));
    add_dropdown_item(&paint->menu_bar[1], create_menu_item("Cut", cut_selection));
    add_dropdown_item(&paint->menu_bar[1], create_menu_item("Paste", paste_selection));
    
    add_dropdown_item(&paint->menu_bar[2], create_menu_item("Help", show_help));
    add_dropdown_item(&paint->menu_bar[2], create_menu_item("About", show_about));
    
    for (int i = 0; i < paint->menu_count; i++) {
        paint->menu_bar[i].background = sfRectangleShape_create();
        if (paint->menu_bar[i].background) {
            sfRectangleShape_setSize(paint->menu_bar[i].background, (sfVector2f){80, MENU_HEIGHT});
            sfRectangleShape_setPosition(paint->menu_bar[i].background, (sfVector2f){i * 80, 0});
            sfRectangleShape_setFillColor(paint->menu_bar[i].background, sfTransparent);
        }
        
        paint->menu_bar[i].sfml_text = sfText_create();
        if (paint->menu_bar[i].sfml_text) {
            sfText_setString(paint->menu_bar[i].sfml_text, paint->menu_bar[i].text);
            sfText_setCharacterSize(paint->menu_bar[i].sfml_text, 14);
            sfText_setFillColor(paint->menu_bar[i].sfml_text, sfBlack);
            sfText_setPosition(paint->menu_bar[i].sfml_text, (sfVector2f){i * 80 + 10, 8});
        }
    }
}

menu_item_t *create_menu_item(char *text, void (*callback)(void *))
{
    menu_item_t *item = malloc(sizeof(menu_item_t));
    if (!item)
        return NULL;
    
    item->text = malloc(strlen(text) + 1);
    if (!item->text) {
        free(item);
        return NULL;
    }
    
    strcpy(item->text, text);
    item->callback = callback;
    item->state = BUTTON_IDLE;
    item->is_dropdown = 0;
    item->dropdown_items = NULL;
    item->dropdown_count = 0;
    item->dropdown_visible = 0;
    item->sfml_text = NULL;
    item->background = NULL;
    
    return item;
}

void add_dropdown_item(menu_item_t *parent, menu_item_t *item)
{
    if (!parent || !item)
        return;
    
    parent->is_dropdown = 1;
    parent->dropdown_count++;
    
    parent->dropdown_items = realloc(parent->dropdown_items, 
                                   sizeof(menu_item_t) * parent->dropdown_count);
    
    if (parent->dropdown_items) {
        parent->dropdown_items[parent->dropdown_count - 1] = *item;
        free(item);
    }
}

void render_dropdown(paint_t *paint, menu_item_t *menu)
{
    if (!menu || !menu->is_dropdown || !menu->dropdown_visible)
        return;
    
    int menu_index = 0;
    for (int i = 0; i < paint->menu_count; i++) {
        if (&paint->menu_bar[i] == menu) {
            menu_index = i;
            break;
        }
    }
    
    sfRectangleShape *dropdown_bg = sfRectangleShape_create();
    if (dropdown_bg) {
        sfRectangleShape_setSize(dropdown_bg, 
            (sfVector2f){120, menu->dropdown_count * 25});
        sfRectangleShape_setPosition(dropdown_bg, 
            (sfVector2f){menu_index * 80, MENU_HEIGHT});
        sfRectangleShape_setFillColor(dropdown_bg, sfColor_fromRGB(240, 240, 240));
        sfRectangleShape_setOutlineThickness(dropdown_bg, 1);
        sfRectangleShape_setOutlineColor(dropdown_bg, sfBlack);
        
        sfRenderWindow_drawRectangleShape(paint->window, dropdown_bg, NULL);
        sfRectangleShape_destroy(dropdown_bg);
    }
    
    if (!paint->font)
        return;
    
    for (int i = 0; i < menu->dropdown_count; i++) {
        sfText *item_text = sfText_create();
        if (item_text) {
            sfText_setFont(item_text, paint->font);
            sfText_setString(item_text, menu->dropdown_items[i].text);
            sfText_setCharacterSize(item_text, 12);
            sfText_setFillColor(item_text, sfBlack);
            sfText_setPosition(item_text, (sfVector2f){
                menu_index * 80 + 5, 
                MENU_HEIGHT + i * 25 + 5
            });
            
            sfRenderWindow_drawText(paint->window, item_text, NULL);
            sfText_destroy(item_text);
        }
    }
}