/*
** EPITECH PROJECT, 2024
** MyWorld
** File description:
** Event handling system
*/

#include "../include/my_world.h"

void handle_events(world_t *world)
{
    if (!world)
        return;
    
    while (sfRenderWindow_pollEvent(world->window, &world->event)) {
        switch (world->event.type) {
            case sfEvtClosed:
                world->running = 0;
                break;
                
            case sfEvtKeyPressed:
                handle_keyboard(world);
                break;
                
            case sfEvtMouseButtonPressed:
                if (world->event.mouseButton.button == sfMouseLeft) {
                    world->mouse_pressed = 1;
                    handle_mouse(world);
                }
                break;
                
            case sfEvtMouseButtonReleased:
                if (world->event.mouseButton.button == sfMouseLeft) {
                    world->mouse_pressed = 0;
                }
                break;
                
            case sfEvtMouseMoved:
                world->mouse_pos.x = world->event.mouseMove.x;
                world->mouse_pos.y = world->event.mouseMove.y;
                if (world->mouse_pressed) {
                    handle_mouse(world);
                }
                break;
                
            case sfEvtMouseWheelScrolled:
                if (world->event.mouseWheelScroll.wheel == sfMouseVerticalWheel) {
                    float zoom_factor = (world->event.mouseWheelScroll.delta > 0) ? 1.1f : 0.9f;
                    world->camera.zoom *= zoom_factor;
                    
                    if (world->camera.zoom < 0.5f)
                        world->camera.zoom = 0.5f;
                    if (world->camera.zoom > 3.0f)
                        world->camera.zoom = 3.0f;
                }
                break;
                
            case sfEvtResized:
                sfRenderWindow_setView(world->window, 
                    sfRenderWindow_getDefaultView(world->window));
                break;
                
            default:
                break;
        }
    }
}

void handle_keyboard(world_t *world)
{
    if (!world)
        return;
    
    float move_speed = 2.0f;
    
    switch (world->event.key.code) {
        case sfKeyEscape:
            world->running = 0;
            break;
            
        case sfKeyUp:
        case sfKeyW:
            world->camera.target.y -= move_speed;
            break;
            
        case sfKeyDown:
        case sfKeyS:
            world->camera.target.y += move_speed;
            break;
            
        case sfKeyLeft:
        case sfKeyA:
            world->camera.target.x -= move_speed;
            break;
            
        case sfKeyRight:
        case sfKeyD:
            world->camera.target.x += move_speed;
            break;
            
        case sfKeyAdd:
        case sfKeyEqual:
            world->camera.zoom *= 1.1f;
            if (world->camera.zoom > 3.0f)
                world->camera.zoom = 3.0f;
            break;
            
        case sfKeySubtract:
        case sfKeyHyphen:
            world->camera.zoom *= 0.9f;
            if (world->camera.zoom < 0.5f)
                world->camera.zoom = 0.5f;
            break;
            
        case sfKeyR:
            world->current_tool = TOOL_RAISE;
            break;
            
        case sfKeyL:
            world->current_tool = TOOL_LOWER;
            break;
            
        case sfKeyF:
            world->current_tool = TOOL_FLATTEN;
            break;
            
        case sfKeyM:
            world->current_tool = TOOL_SMOOTH;
            break;
            
        case sfKeyN:
            world->current_tool = TOOL_NOISE;
            break;
            
        case sfKeyT:
            world->selection_mode = SELECT_TILES;
            break;
            
        case sfKeyC:
            world->selection_mode = SELECT_CORNERS;
            break;
            
        case sfKeyO:
            save_map(world, world->map.filename);
            break;
            
        default:
            break;
    }
}

void handle_mouse(world_t *world)
{
    if (!world)
        return;
    
    if (world->mouse_pos.y < TOOLBAR_HEIGHT) {
        if (handle_button_click(world, world->mouse_pos)) {
            return;
        }
    }
    
    if (world->mouse_pos.y > TOOLBAR_HEIGHT) {
        update_map_selection(world);
    }
}

void update_map_selection(world_t *world)
{
    if (!world || !world->map.tiles)
        return;
    
    vector3_t world_pos = screen_to_world(world, world->mouse_pos);
    
    int tile_x = (int)world_pos.x;
    int tile_y = (int)world_pos.y;
    
    if (tile_x >= 0 && tile_x < world->map.width &&
        tile_y >= 0 && tile_y < world->map.height) {
        
        apply_tool(world, tile_x, tile_y);
    }
}