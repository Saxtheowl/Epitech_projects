/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** Scene management and rendering
*/

#include "../include/my_rpg.h"

void handle_splash_scene(game_t *game)
{
    if (game->event.type == sfEvtKeyPressed || game->event.type == sfEvtMouseButtonPressed) {
        game->current_scene = SCENE_MAIN_MENU;
    }
}

void handle_main_menu_scene(game_t *game)
{
    if (game->event.type == sfEvtMouseButtonPressed) {
        sfVector2i mouse = sfMouse_getPositionRenderWindow(game->window);
        
        for (int i = 0; i < game->button_count; i++) {
            vector2_t mouse_pos = {mouse.x, mouse.y};
            
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
    if (game->event.type == sfEvtKeyPressed) {
        vector2_t direction = {0, 0};
        
        switch (game->event.key.code) {
            case sfKeyZ:
            case sfKeyW:
                direction.y = -1;
                break;
            case sfKeyS:
                direction.y = 1;
                break;
            case sfKeyQ:
            case sfKeyA:
                direction.x = -1;
                break;
            case sfKeyD:
                direction.x = 1;
                break;
            case sfKeyI:
                game->previous_scene = SCENE_GAME;
                game->current_scene = SCENE_INVENTORY;
                break;
            case sfKeySpace:
                {
                    enemy_t *enemy = get_enemy_at_pos(game, game->player.pos);
                    if (enemy && enemy->alive) {
                        init_combat(game, enemy);
                        game->current_scene = SCENE_COMBAT;
                    }
                    
                    npc_t *npc = get_npc_at_pos(game, game->player.pos);
                    if (npc) {
                        start_dialog(game, npc);
                        game->current_scene = SCENE_DIALOG;
                    }
                }
                break;
            default:
                break;
        }
        
        if (direction.x != 0 || direction.y != 0) {
            move_player(game, direction);
        }
    }
    
    if (game->event.type == sfEvtMouseWheelScrolled) {
        float zoom_factor = (game->event.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;
        camera_zoom(game, zoom_factor);
    }
}

void handle_inventory_scene(game_t *game)
{
    if (game->event.type == sfEvtKeyPressed) {
        if (game->event.key.code == sfKeyEscape) {
            game->current_scene = SCENE_GAME;
        }
    }
}

void handle_settings_scene(game_t *game)
{
    if (game->event.type == sfEvtKeyPressed) {
        if (game->event.key.code == sfKeyEscape) {
            game->current_scene = game->previous_scene;
        }
    }
}

void handle_combat_scene(game_t *game)
{
    if (game->event.type == sfEvtKeyPressed) {
        switch (game->event.key.code) {
            case sfKeyNum1:
                player_attack(game, game->combat_enemy);
                process_combat_turn(game);
                break;
            case sfKeyNum2:
                use_item(game, 0);
                process_combat_turn(game);
                break;
            case sfKeyEscape:
                end_combat(game);
                break;
            default:
                break;
        }
    }
}

void handle_dialog_scene(game_t *game)
{
    if (game->event.type == sfEvtKeyPressed) {
        if (game->event.key.code == sfKeySpace || game->event.key.code == sfKeyReturn) {
            game->dialog_line++;
            if (game->dialog_line >= 3) {
                if (game->dialog_npc && game->dialog_npc->has_quest) {
                    start_quest(game, game->dialog_npc->quest_id);
                }
                game->current_scene = SCENE_GAME;
                game->dialog_line = 0;
            }
        }
        
        if (game->event.key.code == sfKeyEscape) {
            game->current_scene = SCENE_GAME;
            game->dialog_line = 0;
        }
    }
}

void render_splash_scene(game_t *game)
{
    if (game->splash_sprite) {
        sfRenderWindow_drawSprite(game->window, game->splash_sprite, NULL);
    }
    
    if (game->font) {
        sfText *title = sfText_create();
        sfText_setFont(title, game->font);
        sfText_setString(title, "MYRPG");
        sfText_setCharacterSize(title, 120);
        sfText_setFillColor(title, sfWhite);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT/2 - 100});
        
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
        
        sfText *subtitle = sfText_create();
        sfText_setFont(subtitle, game->font);
        sfText_setString(subtitle, "Press any key to continue...");
        sfText_setCharacterSize(subtitle, 24);
        sfText_setFillColor(subtitle, sfColor_fromRGB(200, 200, 200));
        sfText_setPosition(subtitle, (sfVector2f){WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2 + 50});
        
        sfRenderWindow_drawText(game->window, subtitle, NULL);
        sfText_destroy(subtitle);
    }
}

void render_main_menu_scene(game_t *game)
{
    sfRectangleShape *bg = sfRectangleShape_create();
    if (bg) {
        sfRectangleShape_setSize(bg, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
        sfRectangleShape_setFillColor(bg, sfColor_fromRGB(20, 20, 40));
        sfRenderWindow_drawRectangleShape(game->window, bg, NULL);
        sfRectangleShape_destroy(bg);
    }
    
    if (game->font) {
        sfText *title = sfText_create();
        sfText_setFont(title, game->font);
        sfText_setString(title, "FANTASY ADVENTURE");
        sfText_setCharacterSize(title, 72);
        sfText_setFillColor(title, sfColor_fromRGB(255, 215, 0));
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 300, 150});
        
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
    }
    
    render_buttons(game);
}

void render_game_scene(game_t *game)
{
    if (game->camera.view) {
        sfRenderWindow_setView(game->window, game->camera.view);
    }
    
    render_map(game);
    
    for (int i = 0; i < MAX_NPCS; i++) {
        if (game->npcs[i].sprite) {
            sfSprite_setPosition(game->npcs[i].sprite, (sfVector2f){
                game->npcs[i].pos.x * TILE_SIZE,
                game->npcs[i].pos.y * TILE_SIZE
            });
            sfRenderWindow_drawSprite(game->window, game->npcs[i].sprite, NULL);
        }
    }
    
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (game->enemies[i].alive && game->enemies[i].sprite) {
            sfSprite_setPosition(game->enemies[i].sprite, (sfVector2f){
                game->enemies[i].pos.x * TILE_SIZE,
                game->enemies[i].pos.y * TILE_SIZE
            });
            sfRenderWindow_drawSprite(game->window, game->enemies[i].sprite, NULL);
        }
    }
    
    if (game->player.sprite) {
        sfSprite_setPosition(game->player.sprite, (sfVector2f){
            game->player.pos.x * TILE_SIZE,
            game->player.pos.y * TILE_SIZE
        });
        sfRenderWindow_drawSprite(game->window, game->player.sprite, NULL);
    }
    
    render_particles(game);
    
    sfRenderWindow_setView(game->window, sfRenderWindow_getDefaultView(game->window));
    render_hud(game);
    render_minimap(game);
}

void render_inventory_scene(game_t *game)
{
    render_game_scene(game);
    
    sfRectangleShape *overlay = sfRectangleShape_create();
    if (overlay) {
        sfRectangleShape_setSize(overlay, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
        sfRectangleShape_setFillColor(overlay, sfColor_fromRGBA(0, 0, 0, 128));
        sfRenderWindow_drawRectangleShape(game->window, overlay, NULL);
        sfRectangleShape_destroy(overlay);
    }
    
    sfRectangleShape *inventory_bg = sfRectangleShape_create();
    if (inventory_bg) {
        sfRectangleShape_setSize(inventory_bg, (sfVector2f){800, 600});
        sfRectangleShape_setPosition(inventory_bg, (sfVector2f){
            (WINDOW_WIDTH - 800) / 2, 
            (WINDOW_HEIGHT - 600) / 2
        });
        sfRectangleShape_setFillColor(inventory_bg, sfColor_fromRGB(40, 40, 60));
        sfRectangleShape_setOutlineThickness(inventory_bg, 3);
        sfRectangleShape_setOutlineColor(inventory_bg, sfColor_fromRGB(255, 215, 0));
        
        sfRenderWindow_drawRectangleShape(game->window, inventory_bg, NULL);
        sfRectangleShape_destroy(inventory_bg);
    }
    
    if (game->font) {
        sfText *title = sfText_create();
        sfText_setFont(title, game->font);
        sfText_setString(title, "INVENTORY");
        sfText_setCharacterSize(title, 36);
        sfText_setFillColor(title, sfWhite);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 250});
        
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
    }
}

void render_settings_scene(game_t *game)
{
    render_main_menu_scene(game);
    
    sfRectangleShape *settings_bg = sfRectangleShape_create();
    if (settings_bg) {
        sfRectangleShape_setSize(settings_bg, (sfVector2f){600, 400});
        sfRectangleShape_setPosition(settings_bg, (sfVector2f){
            (WINDOW_WIDTH - 600) / 2, 
            (WINDOW_HEIGHT - 400) / 2
        });
        sfRectangleShape_setFillColor(settings_bg, sfColor_fromRGB(40, 40, 60));
        sfRectangleShape_setOutlineThickness(settings_bg, 3);
        sfRectangleShape_setOutlineColor(settings_bg, sfColor_fromRGB(255, 215, 0));
        
        sfRenderWindow_drawRectangleShape(game->window, settings_bg, NULL);
        sfRectangleShape_destroy(settings_bg);
    }
    
    if (game->font) {
        sfText *title = sfText_create();
        sfText_setFont(title, game->font);
        sfText_setString(title, "SETTINGS");
        sfText_setCharacterSize(title, 36);
        sfText_setFillColor(title, sfWhite);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 150});
        
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
    }
}

void render_combat_scene(game_t *game)
{
    sfRectangleShape *bg = sfRectangleShape_create();
    if (bg) {
        sfRectangleShape_setSize(bg, (sfVector2f){WINDOW_WIDTH, WINDOW_HEIGHT});
        sfRectangleShape_setFillColor(bg, sfColor_fromRGB(40, 20, 20));
        sfRenderWindow_drawRectangleShape(game->window, bg, NULL);
        sfRectangleShape_destroy(bg);
    }
    
    if (game->font && game->combat_enemy) {
        sfText *title = sfText_create();
        sfText_setFont(title, game->font);
        
        char combat_text[256];
        sprintf(combat_text, "COMBAT: %s", game->combat_enemy->name);
        sfText_setString(title, combat_text);
        sfText_setCharacterSize(title, 48);
        sfText_setFillColor(title, sfRed);
        sfText_setPosition(title, (sfVector2f){WINDOW_WIDTH/2 - 200, 100});
        
        sfRenderWindow_drawText(game->window, title, NULL);
        sfText_destroy(title);
        
        sfText *instructions = sfText_create();
        sfText_setFont(instructions, game->font);
        sfText_setString(instructions, "1 - Attack   2 - Use Item   ESC - Flee");
        sfText_setCharacterSize(instructions, 24);
        sfText_setFillColor(instructions, sfWhite);
        sfText_setPosition(instructions, (sfVector2f){WINDOW_WIDTH/2 - 250, WINDOW_HEIGHT - 100});
        
        sfRenderWindow_drawText(game->window, instructions, NULL);
        sfText_destroy(instructions);
    }
}

void render_dialog_scene(game_t *game)
{
    render_game_scene(game);
    
    sfRectangleShape *dialog_bg = sfRectangleShape_create();
    if (dialog_bg) {
        sfRectangleShape_setSize(dialog_bg, (sfVector2f){WINDOW_WIDTH - 100, 200});
        sfRectangleShape_setPosition(dialog_bg, (sfVector2f){50, WINDOW_HEIGHT - 250});
        sfRectangleShape_setFillColor(dialog_bg, sfColor_fromRGBA(0, 0, 0, 180));
        sfRectangleShape_setOutlineThickness(dialog_bg, 2);
        sfRectangleShape_setOutlineColor(dialog_bg, sfWhite);
        
        sfRenderWindow_drawRectangleShape(game->window, dialog_bg, NULL);
        sfRectangleShape_destroy(dialog_bg);
    }
    
    if (game->font && game->dialog_npc) {
        sfText *npc_name = sfText_create();
        sfText_setFont(npc_name, game->font);
        sfText_setString(npc_name, game->dialog_npc->name);
        sfText_setCharacterSize(npc_name, 24);
        sfText_setFillColor(npc_name, sfColor_fromRGB(255, 215, 0));
        sfText_setPosition(npc_name, (sfVector2f){70, WINDOW_HEIGHT - 240});
        
        sfRenderWindow_drawText(game->window, npc_name, NULL);
        sfText_destroy(npc_name);
        
        sfText *dialog_text = sfText_create();
        sfText_setFont(dialog_text, game->font);
        sfText_setString(dialog_text, game->dialog_npc->dialog);
        sfText_setCharacterSize(dialog_text, 18);
        sfText_setFillColor(dialog_text, sfWhite);
        sfText_setPosition(dialog_text, (sfVector2f){70, WINDOW_HEIGHT - 200});
        
        sfRenderWindow_drawText(game->window, dialog_text, NULL);
        sfText_destroy(dialog_text);
    }
}