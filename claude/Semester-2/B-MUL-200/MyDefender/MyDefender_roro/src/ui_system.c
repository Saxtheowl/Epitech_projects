/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** User interface and button management
*/

#include "../include/my_defender.h"

void init_ui(game_t *game)
{
    game->button_count = 0;
    game->buttons = malloc(sizeof(button_t) * 10);
    
    if (game->current_scene == SCENE_MENU || game->current_scene == SCENE_PAUSE) {
        button_t start_btn = {
            .pos = {WINDOW_WIDTH/2 - 100, 300},
            .size = {200, 50},
            .callback = button_start_game
        };
        
        button_t quit_btn = {
            .pos = {WINDOW_WIDTH/2 - 100, 400},
            .size = {200, 50},
            .callback = button_quit_game
        };
        
        button_t help_btn = {
            .pos = {WINDOW_WIDTH/2 - 100, 350},
            .size = {200, 50},
            .callback = button_how_to_play
        };
        
        if (game->current_scene == SCENE_MENU) {
            game->buttons[game->button_count++] = start_btn;
            game->buttons[game->button_count++] = help_btn;
            game->buttons[game->button_count++] = quit_btn;
        } else {
            button_t resume_btn = {
                .pos = {WINDOW_WIDTH/2 - 100, 250},
                .size = {200, 50},
                .callback = button_resume_game
            };
            
            button_t menu_btn = {
                .pos = {WINDOW_WIDTH/2 - 100, 300},
                .size = {200, 50},
                .callback = button_main_menu
            };
            
            game->buttons[game->button_count++] = resume_btn;
            game->buttons[game->button_count++] = menu_btn;
            game->buttons[game->button_count++] = quit_btn;
        }
    }
    
    for (int i = 0; i < game->button_count; i++) {
        game->buttons[i].shape = sfRectangleShape_create();
        game->buttons[i].text = sfText_create();
        game->buttons[i].is_hovered = 0;
        game->buttons[i].is_clicked = 0;
        
        if (game->buttons[i].shape) {
            sfRectangleShape_setSize(game->buttons[i].shape, game->buttons[i].size);
            sfRectangleShape_setPosition(game->buttons[i].shape, game->buttons[i].pos);
            sfRectangleShape_setFillColor(game->buttons[i].shape, sfColor_fromRGB(100, 100, 100));
            sfRectangleShape_setOutlineThickness(game->buttons[i].shape, 2);
            sfRectangleShape_setOutlineColor(game->buttons[i].shape, sfWhite);
        }
        
        if (game->buttons[i].text && game->font) {
            sfText_setFont(game->buttons[i].text, game->font);
            sfText_setCharacterSize(game->buttons[i].text, 24);
            sfText_setFillColor(game->buttons[i].text, sfWhite);
            
            const char *text_str = "Button";
            if (i == 0 && game->current_scene == SCENE_MENU) text_str = "Start Game";
            else if (i == 0 && game->current_scene == SCENE_PAUSE) text_str = "Resume";
            else if (i == 1 && game->current_scene == SCENE_MENU) text_str = "How to Play";
            else if (i == 1 && game->current_scene == SCENE_PAUSE) text_str = "Main Menu";
            else if (i == 2) text_str = "Quit";
            
            sfText_setString(game->buttons[i].text, text_str);
            
            sfFloatRect text_bounds = sfText_getLocalBounds(game->buttons[i].text);
            sfText_setPosition(game->buttons[i].text, (sfVector2f){
                game->buttons[i].pos.x + (game->buttons[i].size.x - text_bounds.width) / 2,
                game->buttons[i].pos.y + (game->buttons[i].size.y - text_bounds.height) / 2
            });
        }
    }
}

void render_ui(game_t *game)
{
    render_hud(game);
}

void render_hud(game_t *game)
{
    if (!game->font)
        return;
    
    char hud_text[256];
    
    sprintf(hud_text, "HP: %d", game->castle_hp);
    sfText *hp_text = sfText_create();
    if (hp_text) {
        sfText_setFont(hp_text, game->font);
        sfText_setString(hp_text, hud_text);
        sfText_setCharacterSize(hp_text, 20);
        sfText_setFillColor(hp_text, sfWhite);
        sfText_setPosition(hp_text, (sfVector2f){MAP_WIDTH * GRID_SIZE + 10, 10});
        sfRenderWindow_drawText(game->window, hp_text, NULL);
        sfText_destroy(hp_text);
    }
    
    sprintf(hud_text, "Money: $%d", game->money);
    sfText *money_text = sfText_create();
    if (money_text) {
        sfText_setFont(money_text, game->font);
        sfText_setString(money_text, hud_text);
        sfText_setCharacterSize(money_text, 20);
        sfText_setFillColor(money_text, sfGreen);
        sfText_setPosition(money_text, (sfVector2f){MAP_WIDTH * GRID_SIZE + 10, 35});
        sfRenderWindow_drawText(game->window, money_text, NULL);
        sfText_destroy(money_text);
    }
    
    sprintf(hud_text, "Wave: %d", game->wave_number);
    sfText *wave_text = sfText_create();
    if (wave_text) {
        sfText_setFont(wave_text, game->font);
        sfText_setString(wave_text, hud_text);
        sfText_setCharacterSize(wave_text, 20);
        sfText_setFillColor(wave_text, sfYellow);
        sfText_setPosition(wave_text, (sfVector2f){MAP_WIDTH * GRID_SIZE + 10, 60});
        sfRenderWindow_drawText(game->window, wave_text, NULL);
        sfText_destroy(wave_text);
    }
    
    sprintf(hud_text, "Score: %d", game->score);
    sfText *score_text = sfText_create();
    if (score_text) {
        sfText_setFont(score_text, game->font);
        sfText_setString(score_text, hud_text);
        sfText_setCharacterSize(score_text, 20);
        sfText_setFillColor(score_text, sfCyan);
        sfText_setPosition(score_text, (sfVector2f){MAP_WIDTH * GRID_SIZE + 10, 85});
        sfRenderWindow_drawText(game->window, score_text, NULL);
        sfText_destroy(score_text);
    }
}

void render_building_menu(game_t *game)
{
    if (!game->font)
        return;
    
    int menu_x = MAP_WIDTH * GRID_SIZE + 10;
    int menu_y = 120;
    
    const char *building_names[] = {"Wall ($50)", "Basic Tower ($100)", "Slow Tower ($150)", "Heavy Tower ($200)"};
    const char *building_desc[] = {"Blocks enemies", "Fast attack", "Slows enemies", "High damage"};
    
    for (int i = 0; i < BUILD_COUNT - 1; i++) {
        building_type_t type = i + 1;
        
        sfRectangleShape *bg = sfRectangleShape_create();
        if (bg) {
            sfRectangleShape_setSize(bg, (sfVector2f){180, 60});
            sfRectangleShape_setPosition(bg, (sfVector2f){menu_x, menu_y + i * 65});
            
            sfColor bg_color = (game->selected_building == type) ? 
                sfColor_fromRGB(100, 150, 100) : sfColor_fromRGB(60, 60, 60);
            sfRectangleShape_setFillColor(bg, bg_color);
            sfRectangleShape_setOutlineThickness(bg, 1);
            sfRectangleShape_setOutlineColor(bg, sfWhite);
            
            sfRenderWindow_drawRectangleShape(game->window, bg, NULL);
            sfRectangleShape_destroy(bg);
        }
        
        sfText *name_text = sfText_create();
        if (name_text) {
            sfText_setFont(name_text, game->font);
            sfText_setString(name_text, building_names[i]);
            sfText_setCharacterSize(name_text, 14);
            sfText_setFillColor(name_text, sfWhite);
            sfText_setPosition(name_text, (sfVector2f){menu_x + 5, menu_y + i * 65 + 5});
            sfRenderWindow_drawText(game->window, name_text, NULL);
            sfText_destroy(name_text);
        }
        
        sfText *desc_text = sfText_create();
        if (desc_text) {
            sfText_setFont(desc_text, game->font);
            sfText_setString(desc_text, building_desc[i]);
            sfText_setCharacterSize(desc_text, 12);
            sfText_setFillColor(desc_text, sfColor_fromRGB(200, 200, 200));
            sfText_setPosition(desc_text, (sfVector2f){menu_x + 5, menu_y + i * 65 + 25});
            sfRenderWindow_drawText(game->window, desc_text, NULL);
            sfText_destroy(desc_text);
        }
        
        char key_text[16];
        sprintf(key_text, "Key: %d", i + 1);
        sfText *key_label = sfText_create();
        if (key_label) {
            sfText_setFont(key_label, game->font);
            sfText_setString(key_label, key_text);
            sfText_setCharacterSize(key_label, 10);
            sfText_setFillColor(key_label, sfColor_fromRGB(150, 150, 150));
            sfText_setPosition(key_label, (sfVector2f){menu_x + 5, menu_y + i * 65 + 42});
            sfRenderWindow_drawText(game->window, key_label, NULL);
            sfText_destroy(key_label);
        }
    }
    
    if (game->selected_building != BUILD_NONE) {
        sfText *selected_text = sfText_create();
        if (selected_text) {
            sfText_setFont(selected_text, game->font);
            sfText_setString(selected_text, "SELECTED - Click to place\nSpace to cancel");
            sfText_setCharacterSize(selected_text, 12);
            sfText_setFillColor(selected_text, sfGreen);
            sfText_setPosition(selected_text, (sfVector2f){menu_x, menu_y + 280});
            sfRenderWindow_drawText(game->window, selected_text, NULL);
            sfText_destroy(selected_text);
        }
    }
}

button_t *create_button(sfVector2f pos, sfVector2f size, char *text, void (*callback)(void *))
{
    button_t *button = malloc(sizeof(button_t));
    if (!button)
        return NULL;
    
    button->pos = pos;
    button->size = size;
    button->callback = callback;
    button->is_hovered = 0;
    button->is_clicked = 0;
    
    return button;
}

void update_buttons(game_t *game)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
    sfVector2f mouse_pos = {mouse.x, mouse.y};
    
    for (int i = 0; i < game->button_count; i++) {
        int was_hovered = game->buttons[i].is_hovered;
        
        game->buttons[i].is_hovered = (
            mouse_pos.x >= game->buttons[i].pos.x && 
            mouse_pos.x <= game->buttons[i].pos.x + game->buttons[i].size.x &&
            mouse_pos.y >= game->buttons[i].pos.y && 
            mouse_pos.y <= game->buttons[i].pos.y + game->buttons[i].size.y
        );
        
        if (game->buttons[i].shape) {
            sfColor color;
            if (game->buttons[i].is_clicked) {
                color = sfColor_fromRGB(50, 50, 50);
            } else if (game->buttons[i].is_hovered) {
                color = sfColor_fromRGB(150, 150, 150);
            } else {
                color = sfColor_fromRGB(100, 100, 100);
            }
            sfRectangleShape_setFillColor(game->buttons[i].shape, color);
        }
    }
}

void render_buttons(game_t *game)
{
    for (int i = 0; i < game->button_count; i++) {
        if (game->buttons[i].shape) {
            sfRenderWindow_drawRectangleShape(game->window, game->buttons[i].shape, NULL);
        }
        
        if (game->buttons[i].text) {
            sfRenderWindow_drawText(game->window, game->buttons[i].text, NULL);
        }
    }
}