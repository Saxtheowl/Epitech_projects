/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** UI system implementation
*/

#include "../include/my_rpg.h"

void init_ui(game_t *game)
{
    for (int i = 0; i < MAX_BUTTONS; i++) {
        game->ui.buttons[i].active = 0;
        game->ui.buttons[i].text = sfText_create();
        game->ui.buttons[i].shape = sfRectangleShape_create();
        
        if (game->ui.buttons[i].text && game->fonts[0]) {
            sfText_setFont(game->ui.buttons[i].text, game->fonts[0]);
            sfText_setCharacterSize(game->ui.buttons[i].text, 24);
        }
        
        if (game->ui.buttons[i].shape) {
            sfRectangleShape_setSize(game->ui.buttons[i].shape, (sfVector2f){200, 50});
            sfRectangleShape_setFillColor(game->ui.buttons[i].shape, 
                sfColor_fromRGB(100, 100, 100));
            sfRectangleShape_setOutlineThickness(game->ui.buttons[i].shape, 2);
        }
    }
    
    game->ui.health_bar = sfRectangleShape_create();
    game->ui.mana_bar = sfRectangleShape_create();
    game->ui.exp_bar = sfRectangleShape_create();
    
    if (game->ui.health_bar) {
        sfRectangleShape_setSize(game->ui.health_bar, (sfVector2f){200, 20});
        sfRectangleShape_setFillColor(game->ui.health_bar, sfRed);
    }
    
    if (game->ui.mana_bar) {
        sfRectangleShape_setSize(game->ui.mana_bar, (sfVector2f){200, 20});
        sfRectangleShape_setFillColor(game->ui.mana_bar, sfBlue);
    }
    
    if (game->ui.exp_bar) {
        sfRectangleShape_setSize(game->ui.exp_bar, (sfVector2f){300, 10});
        sfRectangleShape_setFillColor(game->ui.exp_bar, sfYellow);
    }
    
    game->ui.info_text = sfText_create();
    if (game->ui.info_text && game->fonts[0]) {
        sfText_setFont(game->ui.info_text, game->fonts[0]);
        sfText_setCharacterSize(game->ui.info_text, 16);
        sfText_setFillColor(game->ui.info_text, sfWhite);
    }
}

void create_button(game_t *game, int id, vector2_t pos, const char *text)
{
    if (id < 0 || id >= MAX_BUTTONS)
        return;
    
    button_t *button = &game->ui.buttons[id];
    button->active = 1;
    button->pos = pos;
    button->state = BUTTON_IDLE;
    strcpy(button->label, text);
    
    if (button->text) {
        sfText_setString(button->text, text);
        sfText_setPosition(button->text, (sfVector2f){pos.x + 10, pos.y + 15});
    }
    
    if (button->shape) {
        sfRectangleShape_setPosition(button->shape, (sfVector2f){pos.x, pos.y});
    }
}

void update_button(game_t *game, int id, sfVector2i mouse_pos)
{
    if (id < 0 || id >= MAX_BUTTONS || !game->ui.buttons[id].active)
        return;
    
    button_t *button = &game->ui.buttons[id];
    
    if (mouse_pos.x >= button->pos.x && mouse_pos.x <= button->pos.x + 200 &&
        mouse_pos.y >= button->pos.y && mouse_pos.y <= button->pos.y + 50) {
        
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            button->state = BUTTON_PRESSED;
        } else {
            button->state = BUTTON_HOVER;
        }
    } else {
        button->state = BUTTON_IDLE;
    }
    
    if (button->shape) {
        switch (button->state) {
            case BUTTON_IDLE:
                sfRectangleShape_setFillColor(button->shape, 
                    sfColor_fromRGB(100, 100, 100));
                sfRectangleShape_setOutlineColor(button->shape, sfWhite);
                break;
            case BUTTON_HOVER:
                sfRectangleShape_setFillColor(button->shape, 
                    sfColor_fromRGB(150, 150, 150));
                sfRectangleShape_setOutlineColor(button->shape, sfYellow);
                break;
            case BUTTON_PRESSED:
                sfRectangleShape_setFillColor(button->shape, 
                    sfColor_fromRGB(80, 80, 80));
                sfRectangleShape_setOutlineColor(button->shape, sfRed);
                break;
        }
    }
}

void render_ui(game_t *game)
{
    if (game->current_scene == SCENE_GAME) {
        render_hud(game);
    }
    
    for (int i = 0; i < MAX_BUTTONS; i++) {
        if (game->ui.buttons[i].active) {
            if (game->ui.buttons[i].shape) {
                sfRenderWindow_drawRectangleShape(game->window, 
                    game->ui.buttons[i].shape, NULL);
            }
            if (game->ui.buttons[i].text) {
                sfRenderWindow_drawText(game->window, 
                    game->ui.buttons[i].text, NULL);
            }
        }
    }
}

void render_hud(game_t *game)
{
    if (game->ui.health_bar) {
        float health_ratio = (float)game->player.stats.health / 
                           game->player.stats.max_health;
        sfRectangleShape_setSize(game->ui.health_bar, 
            (sfVector2f){200 * health_ratio, 20});
        sfRectangleShape_setPosition(game->ui.health_bar, (sfVector2f){10, 10});
        sfRenderWindow_drawRectangleShape(game->window, game->ui.health_bar, NULL);
    }
    
    if (game->ui.mana_bar) {
        float mana_ratio = (float)game->player.stats.mana / 
                          game->player.stats.max_mana;
        sfRectangleShape_setSize(game->ui.mana_bar, 
            (sfVector2f){200 * mana_ratio, 20});
        sfRectangleShape_setPosition(game->ui.mana_bar, (sfVector2f){10, 35});
        sfRenderWindow_drawRectangleShape(game->window, game->ui.mana_bar, NULL);
    }
    
    if (game->ui.exp_bar) {
        float exp_ratio = (float)game->player.stats.experience / 
                         game->player.stats.exp_to_next;
        sfRectangleShape_setSize(game->ui.exp_bar, 
            (sfVector2f){300 * exp_ratio, 10});
        sfRectangleShape_setPosition(game->ui.exp_bar, 
            (sfVector2f){WINDOW_WIDTH - 310, 10});
        sfRenderWindow_drawRectangleShape(game->window, game->ui.exp_bar, NULL);
    }
    
    if (game->ui.info_text) {
        char info[256];
        sprintf(info, "Level: %d | Gold: %d | HP: %d/%d", 
            game->player.stats.level, game->player.stats.gold,
            game->player.stats.health, game->player.stats.max_health);
        sfText_setString(game->ui.info_text, info);
        sfText_setPosition(game->ui.info_text, (sfVector2f){10, WINDOW_HEIGHT - 30});
        sfRenderWindow_drawText(game->window, game->ui.info_text, NULL);
    }
}