/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Dialog windows (file, help, about)
*/

#include "../include/my_paint.h"

void show_help(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    paint->show_help_dialog = 1;
    
    for (int i = 0; i < paint->menu_count; i++) {
        paint->menu_bar[i].dropdown_visible = 0;
    }
}

void show_about(void *data)
{
    paint_t *paint = (paint_t *)data;
    
    if (!paint)
        return;
    
    paint->show_about_dialog = 1;
    
    for (int i = 0; i < paint->menu_count; i++) {
        paint->menu_bar[i].dropdown_visible = 0;
    }
}

void render_file_dialog(paint_t *paint)
{
    if (!paint || !paint->font)
        return;
    
    sfRectangleShape *dialog_bg = sfRectangleShape_create();
    if (!dialog_bg)
        return;
    
    sfRectangleShape_setSize(dialog_bg, (sfVector2f){400, 200});
    sfRectangleShape_setPosition(dialog_bg, (sfVector2f){
        (WINDOW_WIDTH - 400) / 2, 
        (WINDOW_HEIGHT - 200) / 2
    });
    sfRectangleShape_setFillColor(dialog_bg, sfColor_fromRGB(240, 240, 240));
    sfRectangleShape_setOutlineThickness(dialog_bg, 2);
    sfRectangleShape_setOutlineColor(dialog_bg, sfBlack);
    
    sfRenderWindow_drawRectangleShape(paint->window, dialog_bg, NULL);
    
    sfText *title = sfText_create();
    if (title) {
        sfText_setFont(title, paint->font);
        sfText_setString(title, "File Dialog");
        sfText_setCharacterSize(title, 18);
        sfText_setFillColor(title, sfBlack);
        sfText_setPosition(title, (sfVector2f){
            (WINDOW_WIDTH - 400) / 2 + 20, 
            (WINDOW_HEIGHT - 200) / 2 + 20
        });
        
        sfRenderWindow_drawText(paint->window, title, NULL);
        sfText_destroy(title);
    }
    
    sfText *instruction = sfText_create();
    if (instruction) {
        sfText_setFont(instruction, paint->font);
        sfText_setString(instruction, "Enter filename: (Press Enter to confirm, Escape to cancel)");
        sfText_setCharacterSize(instruction, 12);
        sfText_setFillColor(instruction, sfBlack);
        sfText_setPosition(instruction, (sfVector2f){
            (WINDOW_WIDTH - 400) / 2 + 20, 
            (WINDOW_HEIGHT - 200) / 2 + 60
        });
        
        sfRenderWindow_drawText(paint->window, instruction, NULL);
        sfText_destroy(instruction);
    }
    
    sfRectangleShape *input_bg = sfRectangleShape_create();
    if (input_bg) {
        sfRectangleShape_setSize(input_bg, (sfVector2f){360, 30});
        sfRectangleShape_setPosition(input_bg, (sfVector2f){
            (WINDOW_WIDTH - 400) / 2 + 20, 
            (WINDOW_HEIGHT - 200) / 2 + 100
        });
        sfRectangleShape_setFillColor(input_bg, sfWhite);
        sfRectangleShape_setOutlineThickness(input_bg, 1);
        sfRectangleShape_setOutlineColor(input_bg, sfBlack);
        
        sfRenderWindow_drawRectangleShape(paint->window, input_bg, NULL);
        sfRectangleShape_destroy(input_bg);
    }
    
    sfText *filename_text = sfText_create();
    if (filename_text) {
        sfText_setFont(filename_text, paint->font);
        sfText_setString(filename_text, paint->filename);
        sfText_setCharacterSize(filename_text, 14);
        sfText_setFillColor(filename_text, sfBlack);
        sfText_setPosition(filename_text, (sfVector2f){
            (WINDOW_WIDTH - 400) / 2 + 25, 
            (WINDOW_HEIGHT - 200) / 2 + 105
        });
        
        sfRenderWindow_drawText(paint->window, filename_text, NULL);
        sfText_destroy(filename_text);
    }
    
    sfRectangleShape_destroy(dialog_bg);
}

void render_help_dialog(paint_t *paint)
{
    if (!paint || !paint->font)
        return;
    
    sfRectangleShape *dialog_bg = sfRectangleShape_create();
    if (!dialog_bg)
        return;
    
    sfRectangleShape_setSize(dialog_bg, (sfVector2f){500, 300});
    sfRectangleShape_setPosition(dialog_bg, (sfVector2f){
        (WINDOW_WIDTH - 500) / 2, 
        (WINDOW_HEIGHT - 300) / 2
    });
    sfRectangleShape_setFillColor(dialog_bg, sfColor_fromRGB(240, 240, 240));
    sfRectangleShape_setOutlineThickness(dialog_bg, 2);
    sfRectangleShape_setOutlineColor(dialog_bg, sfBlack);
    
    sfRenderWindow_drawRectangleShape(paint->window, dialog_bg, NULL);
    
    const char *help_text[] = {
        "MyPaint - Help",
        "",
        "Tools:",
        "- Pencil: Click and drag to draw",
        "- Eraser: Click and drag to erase",
        "- Rectangle: Click and drag to draw rectangles",
        "- Circle: Click and drag to draw circles",
        "- Selection: Click and drag to select areas",
        "",
        "Shortcuts:",
        "- Escape: Cancel selection or close dialogs",
        "",
        "Menu:",
        "- File: New, Open, Save files",
        "- Edit: Tool selection, Copy/Cut/Paste",
        "- Help: This dialog and About",
        "",
        "Press Escape to close this dialog"
    };
    
    for (int i = 0; i < 17; i++) {
        sfText *line = sfText_create();
        if (line) {
            sfText_setFont(line, paint->font);
            sfText_setString(line, help_text[i]);
            sfText_setCharacterSize(line, (i == 0) ? 16 : 12);
            sfText_setFillColor(line, sfBlack);
            sfText_setPosition(line, (sfVector2f){
                (WINDOW_WIDTH - 500) / 2 + 20, 
                (WINDOW_HEIGHT - 300) / 2 + 20 + i * 15
            });
            
            sfRenderWindow_drawText(paint->window, line, NULL);
            sfText_destroy(line);
        }
    }
    
    sfRectangleShape_destroy(dialog_bg);
}

void render_about_dialog(paint_t *paint)
{
    if (!paint || !paint->font)
        return;
    
    sfRectangleShape *dialog_bg = sfRectangleShape_create();
    if (!dialog_bg)
        return;
    
    sfRectangleShape_setSize(dialog_bg, (sfVector2f){400, 200});
    sfRectangleShape_setPosition(dialog_bg, (sfVector2f){
        (WINDOW_WIDTH - 400) / 2, 
        (WINDOW_HEIGHT - 200) / 2
    });
    sfRectangleShape_setFillColor(dialog_bg, sfColor_fromRGB(240, 240, 240));
    sfRectangleShape_setOutlineThickness(dialog_bg, 2);
    sfRectangleShape_setOutlineColor(dialog_bg, sfBlack);
    
    sfRenderWindow_drawRectangleShape(paint->window, dialog_bg, NULL);
    
    const char *about_text[] = {
        "About MyPaint",
        "",
        "MyPaint - Picture Editor",
        "Version 1.0",
        "",
        "A simple paint application built with CSFML",
        "Created for Epitech B-MUL-200 project",
        "",
        "Login: roro",
        "",
        "Press Escape to close this dialog"
    };
    
    for (int i = 0; i < 11; i++) {
        sfText *line = sfText_create();
        if (line) {
            sfText_setFont(line, paint->font);
            sfText_setString(line, about_text[i]);
            sfText_setCharacterSize(line, (i == 0) ? 16 : 12);
            sfText_setFillColor(line, sfBlack);
            sfText_setPosition(line, (sfVector2f){
                (WINDOW_WIDTH - 400) / 2 + 20, 
                (WINDOW_HEIGHT - 200) / 2 + 20 + i * 15
            });
            
            sfRenderWindow_drawText(paint->window, line, NULL);
            sfText_destroy(line);
        }
    }
    
    sfRectangleShape_destroy(dialog_bg);
}

void handle_dialog_input(paint_t *paint)
{
    if (paint->event.type == sfEvtKeyPressed) {
        if (paint->event.key.code == sfKeyEscape) {
            paint->show_file_dialog = 0;
            paint->show_help_dialog = 0;
            paint->show_about_dialog = 0;
        } else if (paint->show_file_dialog && paint->event.key.code == sfKeyReturn) {
            if (strlen(paint->filename) > 0) {
                save_image(paint, paint->filename);
            }
            paint->show_file_dialog = 0;
        }
    } else if (paint->show_file_dialog && paint->event.type == sfEvtTextEntered) {
        if (paint->event.text.unicode >= 32 && paint->event.text.unicode < 127) {
            int len = strlen(paint->filename);
            if (len < MAX_FILENAME - 1) {
                paint->filename[len] = (char)paint->event.text.unicode;
                paint->filename[len + 1] = '\0';
            }
        } else if (paint->event.text.unicode == 8 && strlen(paint->filename) > 0) {
            paint->filename[strlen(paint->filename) - 1] = '\0';
        }
    }
}