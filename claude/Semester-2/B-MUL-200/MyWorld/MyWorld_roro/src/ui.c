/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** User interface system
*/

#include "../include/my_world.h"

void init_ui(world_t *world)
{
    if (!world)
        return;
    
    world->ui.font = sfFont_createFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    
    world->ui.help_text = sfText_create();
    if (world->ui.help_text) {
        if (world->ui.font)
            sfText_setFont(world->ui.help_text, world->ui.font);
        sfText_setCharacterSize(world->ui.help_text, 14);
        sfText_setFillColor(world->ui.help_text, sfWhite);
        sfText_setString(world->ui.help_text, "Hover over tools for help");
    }
    
    world->ui.toolbar = sfRectangleShape_create();
    if (world->ui.toolbar) {
        sfRectangleShape_setSize(world->ui.toolbar, 
            (sfVector2f){WINDOW_WIDTH, TOOLBAR_HEIGHT});
        sfRectangleShape_setFillColor(world->ui.toolbar, 
            sfColor_fromRGB(60, 60, 60));
        sfRectangleShape_setPosition(world->ui.toolbar, (sfVector2f){0, 0});
    }
    
    world->ui.size_input_bg = sfRectangleShape_create();
    if (world->ui.size_input_bg) {
        sfRectangleShape_setSize(world->ui.size_input_bg, (sfVector2f){100, 25});
        sfRectangleShape_setFillColor(world->ui.size_input_bg, sfWhite);
        sfRectangleShape_setPosition(world->ui.size_input_bg, (sfVector2f){10, 50});
    }
    
    world->ui.size_input_text = sfText_create();
    if (world->ui.size_input_text) {
        if (world->ui.font)
            sfText_setFont(world->ui.size_input_text, world->ui.font);
        sfText_setCharacterSize(world->ui.size_input_text, 16);
        sfText_setFillColor(world->ui.size_input_text, sfBlack);
        sfText_setPosition(world->ui.size_input_text, (sfVector2f){15, 52});
    }
    
    strcpy(world->ui.size_input, "32x32");
    world->ui.size_input_active = 0;
    world->ui.effect_size = 3;
    world->ui.button_count = 0;
    
    create_button(world, (vector2_t){10, 10}, (vector2_t){60, 30}, "Raise", TOOL_RAISE);
    create_button(world, (vector2_t){80, 10}, (vector2_t){60, 30}, "Lower", TOOL_LOWER);
    create_button(world, (vector2_t){150, 10}, (vector2_t){60, 30}, "Flatten", TOOL_FLATTEN);
    create_button(world, (vector2_t){220, 10}, (vector2_t){60, 30}, "Smooth", TOOL_SMOOTH);
    create_button(world, (vector2_t){290, 10}, (vector2_t){60, 30}, "Noise", TOOL_NOISE);
    create_button(world, (vector2_t){360, 10}, (vector2_t){60, 30}, "Reset", TOOL_RESET);
    create_button(world, (vector2_t){430, 10}, (vector2_t){60, 30}, "Tiles", TOOL_SELECT_TILES);
    create_button(world, (vector2_t){500, 10}, (vector2_t){60, 30}, "Corners", TOOL_SELECT_CORNERS);
    create_button(world, (vector2_t){570, 10}, (vector2_t){30, 30}, "+", TOOL_INCREASE_SIZE);
    create_button(world, (vector2_t){610, 10}, (vector2_t){30, 30}, "-", TOOL_DECREASE_SIZE);
}

void destroy_ui(ui_t *ui)
{
    if (!ui)
        return;
    
    for (int i = 0; i < ui->button_count; i++) {
        if (ui->buttons[i].shape)
            sfRectangleShape_destroy(ui->buttons[i].shape);
        if (ui->buttons[i].text)
            sfText_destroy(ui->buttons[i].text);
    }
    
    if (ui->help_text)
        sfText_destroy(ui->help_text);
    if (ui->toolbar)
        sfRectangleShape_destroy(ui->toolbar);
    if (ui->size_input_bg)
        sfRectangleShape_destroy(ui->size_input_bg);
    if (ui->size_input_text)
        sfText_destroy(ui->size_input_text);
    if (ui->font)
        sfFont_destroy(ui->font);
}

void create_button(world_t *world, vector2_t pos, vector2_t size, 
                   const char *label, tool_type_t tool)
{
    if (!world || world->ui.button_count >= MAX_BUTTONS)
        return;
    
    button_t *button = &world->ui.buttons[world->ui.button_count];
    
    button->shape = sfRectangleShape_create();
    button->text = sfText_create();
    button->pos = pos;
    button->size = size;
    button->tool = tool;
    button->state = BUTTON_IDLE;
    button->active = 1;
    strcpy(button->label, label);
    
    if (button->shape) {
        sfRectangleShape_setSize(button->shape, (sfVector2f){size.x, size.y});
        sfRectangleShape_setPosition(button->shape, (sfVector2f){pos.x, pos.y});
        sfRectangleShape_setFillColor(button->shape, sfColor_fromRGB(100, 100, 100));
        sfRectangleShape_setOutlineThickness(button->shape, 1);
        sfRectangleShape_setOutlineColor(button->shape, sfWhite);
    }
    
    if (button->text) {
        if (world->ui.font)
            sfText_setFont(button->text, world->ui.font);
        sfText_setString(button->text, label);
        sfText_setCharacterSize(button->text, 12);
        sfText_setFillColor(button->text, sfWhite);
        
        sfFloatRect text_bounds = sfText_getLocalBounds(button->text);
        sfText_setPosition(button->text, (sfVector2f){
            pos.x + (size.x - text_bounds.width) / 2,
            pos.y + (size.y - text_bounds.height) / 2 - 2
        });
    }
    
    switch (tool) {
        case TOOL_RAISE:
            strcpy(button->tooltip, "Raise terrain height");
            break;
        case TOOL_LOWER:
            strcpy(button->tooltip, "Lower terrain height");
            break;
        case TOOL_FLATTEN:
            strcpy(button->tooltip, "Flatten selected area");
            break;
        case TOOL_SMOOTH:
            strcpy(button->tooltip, "Smooth terrain variations");
            break;
        case TOOL_NOISE:
            strcpy(button->tooltip, "Add random noise");
            break;
        case TOOL_RESET:
            strcpy(button->tooltip, "Reset to flat terrain");
            break;
        case TOOL_SELECT_TILES:
            strcpy(button->tooltip, "Select tiles mode");
            break;
        case TOOL_SELECT_CORNERS:
            strcpy(button->tooltip, "Select corners mode");
            break;
        case TOOL_INCREASE_SIZE:
            strcpy(button->tooltip, "Increase effect size");
            break;
        case TOOL_DECREASE_SIZE:
            strcpy(button->tooltip, "Decrease effect size");
            break;
    }
    
    world->ui.button_count++;
}

void update_ui(world_t *world)
{
    if (!world)
        return;
    
    update_button_states(world);
    
    if (world->ui.size_input_text) {
        char display_text[32];
        sprintf(display_text, "%s (Size: %d)", world->ui.size_input, world->ui.effect_size);
        sfText_setString(world->ui.size_input_text, display_text);
    }
}

void update_button_states(world_t *world)
{
    if (!world)
        return;
    
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(world->window);
    
    for (int i = 0; i < world->ui.button_count; i++) {
        button_t *button = &world->ui.buttons[i];
        
        if (!button->active || !button->shape)
            continue;
        
        int hover = is_point_in_rect((vector2_t){mouse_pos.x, mouse_pos.y},
                                    button->pos, button->size);
        
        if (hover) {
            if (sfMouse_isButtonPressed(sfMouseLeft)) {
                button->state = BUTTON_CLICKED;
            } else {
                button->state = BUTTON_HOVER;
                if (world->ui.help_text) {
                    sfText_setString(world->ui.help_text, button->tooltip);
                }
            }
        } else {
            button->state = BUTTON_IDLE;
        }
        
        sfColor color;
        switch (button->state) {
            case BUTTON_IDLE:
                color = (world->current_tool == button->tool) ? 
                    sfColor_fromRGB(80, 120, 80) : sfColor_fromRGB(100, 100, 100);
                break;
            case BUTTON_HOVER:
                color = sfColor_fromRGB(120, 120, 120);
                break;
            case BUTTON_CLICKED:
                color = sfColor_fromRGB(80, 80, 80);
                break;
        }
        
        sfRectangleShape_setFillColor(button->shape, color);
    }
}

void render_ui(world_t *world)
{
    if (!world)
        return;
    
    if (world->ui.toolbar)
        sfRenderWindow_drawRectangleShape(world->window, world->ui.toolbar, NULL);
    
    if (world->ui.size_input_bg)
        sfRenderWindow_drawRectangleShape(world->window, world->ui.size_input_bg, NULL);
    
    if (world->ui.size_input_text)
        sfRenderWindow_drawText(world->window, world->ui.size_input_text, NULL);
    
    for (int i = 0; i < world->ui.button_count; i++) {
        if (world->ui.buttons[i].active) {
            if (world->ui.buttons[i].shape)
                sfRenderWindow_drawRectangleShape(world->window, 
                    world->ui.buttons[i].shape, NULL);
            if (world->ui.buttons[i].text)
                sfRenderWindow_drawText(world->window, 
                    world->ui.buttons[i].text, NULL);
        }
    }
    
    if (world->ui.help_text) {
        sfText_setPosition(world->ui.help_text, 
            (sfVector2f){WINDOW_WIDTH - 300, WINDOW_HEIGHT - 30});
        sfRenderWindow_drawText(world->window, world->ui.help_text, NULL);
    }
}

int handle_button_click(world_t *world, vector2_t mouse_pos)
{
    if (!world)
        return 0;
    
    for (int i = 0; i < world->ui.button_count; i++) {
        button_t *button = &world->ui.buttons[i];
        
        if (!button->active)
            continue;
        
        if (is_point_in_rect(mouse_pos, button->pos, button->size)) {
            switch (button->tool) {
                case TOOL_SELECT_TILES:
                    world->selection_mode = SELECT_TILES;
                    break;
                case TOOL_SELECT_CORNERS:
                    world->selection_mode = SELECT_CORNERS;
                    break;
                case TOOL_INCREASE_SIZE:
                    world->ui.effect_size = (world->ui.effect_size < 10) ? 
                        world->ui.effect_size + 1 : 10;
                    break;
                case TOOL_DECREASE_SIZE:
                    world->ui.effect_size = (world->ui.effect_size > 1) ? 
                        world->ui.effect_size - 1 : 1;
                    break;
                default:
                    world->current_tool = button->tool;
                    break;
            }
            return 1;
        }
    }
    
    return 0;
}