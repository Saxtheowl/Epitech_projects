/*
** EPITECH PROJECT, 2024
** MyDefender
** File description:
** Scene management and rendering
*/

#include "../include/my_defender.h"

void handle_menu_scene(game_t *game)
{
    if (game->event.type == sfEvtMouseButtonPressed) {
        for (int i = 0; i < game->button_count; i++) {
            sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
            sfVector2f mouse_pos = {mouse.x, mouse.y};
            
            if (mouse_pos.x >= game->buttons[i].pos.x && 
                mouse_pos.x <= game->buttons[i].pos.x + game->buttons[i].size.x &&
                mouse_pos.y >= game->buttons[i].pos.y && 
                mouse_pos.y <= game->buttons[i].pos.y + game->buttons[i].size.y) {
                
                if (game->buttons[i].callback)
                    game->buttons[i].callback(game);
            }
        }
    }
}

void handle_game_scene(game_t *game)
{
    if (game->event.type == sfEvtMouseButtonPressed) {
        if (game->event.mouseButton.button == sfMouseLeft) {
            sfVector2f mouse_pos = {game->event.mouseButton.x, game->event.mouseButton.y};
            
            if (mouse_pos.y < MAP_HEIGHT * GRID_SIZE && mouse_pos.x < MAP_WIDTH * GRID_SIZE) {
                sfVector2i grid_pos = {mouse_pos.x / GRID_SIZE, mouse_pos.y / GRID_SIZE};
                
                if (game->selected_building != BUILD_NONE && 
                    game->grid[grid_pos.y][grid_pos.x] == BUILD_NONE) {
                    
                    int cost = get_building_cost(game->selected_building);
                    if (game->money >= cost) {
                        if (place_building(game, grid_pos.x, grid_pos.y, game->selected_building)) {
                            game->money -= cost;
                            play_sound(game, 0);
                        }
                    }
                }
            } else {
                if (mouse_pos.x > MAP_WIDTH * GRID_SIZE + 10 && mouse_pos.x < WINDOW_WIDTH - 10 &&
                    mouse_pos.y > 50 && mouse_pos.y < 350) {
                    
                    int building_index = (mouse_pos.y - 50) / 60;
                    if (building_index >= 0 && building_index < BUILD_COUNT - 1) {
                        game->selected_building = building_index + 1;
                    }
                }
            }
        }
    }
    
    if (game->event.type == sfEvtKeyPressed) {
        if (game->event.key.code >= sfKey1 && game->event.key.code <= sfKey4) {
            game->selected_building = game->event.key.code - sfKey1 + 1;
        }
        if (game->event.key.code == sfKeySpace) {
            game->selected_building = BUILD_NONE;
        }
    }
}

void handle_pause_scene(game_t *game)
{
    handle_menu_scene(game);
}

void render_menu_scene(game_t *game)
{
    if (game->background)
        sfRenderWindow_drawSprite(game->window, game->background, NULL);
    
    sfText *title = sfText_create();
    if (title && game->font) {
        sfText_setFont(title, game->font);
        sfText_setString(title, "MY DEFENDER");
        sfText_setCharacterSize(title, 72);
        sfText_setFillColor(title, sfWhite);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 200, 100});
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
    }
    
    render_buttons(game);
}

void render_game_scene(game_t *game)
{
    if (game->background)
        sfRenderWindow_drawSprite(game->window, game->background, NULL);
    
    for (int y = 0; y <= MAP_HEIGHT; y++) {
        sfVertex line[2] = {
            {{0, y * GRID_SIZE}, sfColor_fromRGB(100, 100, 100), {0, 0}},
            {{MAP_WIDTH * GRID_SIZE, y * GRID_SIZE}, sfColor_fromRGB(100, 100, 100), {0, 0}}
        };
        sfRenderWindow_drawPrimitives(game->window, line, 2, sfLines, NULL);
    }
    
    for (int x = 0; x <= MAP_WIDTH; x++) {
        sfVertex line[2] = {
            {{x * GRID_SIZE, 0}, sfColor_fromRGB(100, 100, 100), {0, 0}},
            {{x * GRID_SIZE, MAP_HEIGHT * GRID_SIZE}, sfColor_fromRGB(100, 100, 100), {0, 0}}
        };
        sfRenderWindow_drawPrimitives(game->window, line, 2, sfLines, NULL);
    }
    
    render_buildings(game);
    render_enemies(game);
    render_bullets(game);
    render_ui(game);
    render_building_menu(game);
}

void render_pause_scene(game_t *game)
{
    render_game_scene(game);
    
    sfRectangleShape *overlay = sfRectangleShape_create();
    if (overlay) {
        sfRectangleShape_setSize(overlay, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
        sfRectangleShape_setFillColor(overlay, sfColor_fromRGBA(0, 0, 0, 128));
        sfRenderWindow_drawRectangleShape(game->window, overlay, NULL);
        sfRectangleShape_destroy(overlay);
    }
    
    sfText *pause_text = sfText_create();
    if (pause_text && game->font) {
        sfText_setFont(pause_text, game->font);
        sfText_setString(pause_text, "PAUSED");
        sfText_setCharacterSize(pause_text, 64);
        sfText_setFillColor(pause_text, sfWhite);
        sfText_setPosition(pause_text, (sfVector2f){WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT/2 - 100});
        sfRenderWindow_drawText(game->window, pause_text, NULL);
        sfText_destroy(pause_text);
    }
    
    render_buttons(game);
}