/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** Core application logic and initialization
*/

#include "../include/my_paint.h"

int my_paint(void)
{
    paint_t *paint = init_paint();
    
    if (!paint)
        return 84;
    
    main_loop(paint);
    destroy_paint(paint);
    return 0;
}

paint_t *init_paint(void)
{
    paint_t *paint = malloc(sizeof(paint_t));
    
    if (!paint)
        return NULL;
    
    paint->window = sfRenderWindow_create((sfVideoMode){WINDOW_WIDTH, WINDOW_HEIGHT, 32},
                                         "MyPaint - Picture Editor", 
                                         sfResize | sfClose | sfMinimize, NULL);
    if (!paint->window) {
        free(paint);
        return NULL;
    }
    
    sfRenderWindow_setFramerateLimit(paint->window, 60);
    
    paint->zoom_level = 1.0f;
    paint->current_tool = TOOL_PENCIL;
    paint->drawing = 0;
    paint->current_layer = 0;
    paint->layer_count = 1;
    paint->show_file_dialog = 0;
    paint->show_help_dialog = 0;
    paint->show_about_dialog = 0;
    paint->filename[0] = '\0';
    
    paint->selection.active = 0;
    paint->selection.content = NULL;
    paint->selection.sprite = NULL;
    
    paint->tool_settings.pencil_thickness = 2;
    paint->tool_settings.eraser_shape = ERASER_CIRCLE;
    paint->tool_settings.eraser_size = 10;
    paint->tool_settings.current_color = create_color(0, 0, 0, 255);
    paint->tool_settings.shape_filled = 0;
    
    load_assets(paint);
    init_canvas(paint);
    init_layers(paint);
    init_tools(paint);
    init_ui(paint);
    
    return paint;
}

void destroy_paint(paint_t *paint)
{
    if (!paint)
        return;
    
    if (paint->window)
        sfRenderWindow_destroy(paint->window);
    
    if (paint->canvas)
        sfRenderTexture_destroy(paint->canvas);
    
    if (paint->canvas_sprite)
        sfSprite_destroy(paint->canvas_sprite);
    
    if (paint->canvas_view)
        sfView_destroy(paint->canvas_view);
    
    for (int i = 0; i < paint->layer_count; i++) {
        if (paint->layers[i].texture)
            sfRenderTexture_destroy(paint->layers[i].texture);
        if (paint->layers[i].sprite)
            sfSprite_destroy(paint->layers[i].sprite);
    }
    
    if (paint->selection.content)
        sfTexture_destroy(paint->selection.content);
    if (paint->selection.sprite)
        sfSprite_destroy(paint->selection.sprite);
    
    if (paint->font)
        sfFont_destroy(paint->font);
    
    for (int i = 0; i < TOOL_COUNT; i++) {
        if (paint->tool_icons[i])
            sfTexture_destroy(paint->tool_icons[i]);
    }
    
    if (paint->menu_bar) {
        for (int i = 0; i < paint->menu_count; i++) {
            if (paint->menu_bar[i].sfml_text)
                sfText_destroy(paint->menu_bar[i].sfml_text);
            if (paint->menu_bar[i].background)
                sfRectangleShape_destroy(paint->menu_bar[i].background);
            free(paint->menu_bar[i].text);
        }
        free(paint->menu_bar);
    }
    
    if (paint->toolbar_buttons) {
        for (int i = 0; i < paint->toolbar_button_count; i++) {
            if (paint->toolbar_buttons[i].shape)
                sfRectangleShape_destroy(paint->toolbar_buttons[i].shape);
            if (paint->toolbar_buttons[i].text)
                sfText_destroy(paint->toolbar_buttons[i].text);
            if (paint->toolbar_buttons[i].icon)
                sfSprite_destroy(paint->toolbar_buttons[i].icon);
        }
        free(paint->toolbar_buttons);
    }
    
    if (paint->color_palette) {
        for (int i = 0; i < paint->palette_size; i++) {
            if (paint->color_palette[i].shape)
                sfRectangleShape_destroy(paint->color_palette[i].shape);
        }
        free(paint->color_palette);
    }
    
    free(paint);
}

void main_loop(paint_t *paint)
{
    while (sfRenderWindow_isOpen(paint->window)) {
        handle_events(paint);
        update_paint(paint);
        render_paint(paint);
    }
}

void handle_events(paint_t *paint)
{
    while (sfRenderWindow_pollEvent(paint->window, &paint->event)) {
        if (paint->event.type == sfEvtClosed)
            sfRenderWindow_close(paint->window);
        
        if (paint->show_file_dialog || paint->show_help_dialog || paint->show_about_dialog) {
            handle_dialog_input(paint);
            continue;
        }
        
        switch (paint->event.type) {
            case sfEvtMouseButtonPressed:
                if (paint->event.mouseButton.button == sfMouseLeft) {
                    sfVector2i mouse_pos = {paint->event.mouseButton.x, paint->event.mouseButton.y};
                    
                    if (mouse_pos.y < MENU_HEIGHT) {
                        handle_menu_click(paint, mouse_pos);
                    } else if (mouse_pos.x < TOOLBAR_WIDTH) {
                        handle_toolbar_click(paint, mouse_pos);
                    } else if (mouse_pos.x >= CANVAS_X && mouse_pos.x < CANVAS_X + CANVAS_WIDTH &&
                              mouse_pos.y >= CANVAS_Y && mouse_pos.y < CANVAS_Y + CANVAS_HEIGHT) {
                        
                        paint->drawing = 1;
                        sfVector2i canvas_pos = {mouse_pos.x - CANVAS_X, mouse_pos.y - CANVAS_Y};
                        paint->last_mouse_pos = canvas_pos;
                        
                        switch (paint->current_tool) {
                            case TOOL_PENCIL:
                                use_pencil(paint, canvas_pos);
                                break;
                            case TOOL_ERASER:
                                use_eraser(paint, canvas_pos);
                                break;
                            case TOOL_SELECTION:
                                start_selection(paint, canvas_pos);
                                break;
                            default:
                                break;
                        }
                    } else {
                        handle_palette_click(paint, mouse_pos);
                    }
                }
                break;
                
            case sfEvtMouseButtonReleased:
                if (paint->event.mouseButton.button == sfMouseLeft) {
                    paint->drawing = 0;
                    if (paint->current_tool == TOOL_SELECTION && paint->selection.active) {
                        end_selection(paint);
                    }
                }
                break;
                
            case sfEvtMouseMoved:
                if (paint->drawing) {
                    sfVector2i mouse_pos = {paint->event.mouseMove.x, paint->event.mouseMove.y};
                    
                    if (mouse_pos.x >= CANVAS_X && mouse_pos.x < CANVAS_X + CANVAS_WIDTH &&
                        mouse_pos.y >= CANVAS_Y && mouse_pos.y < CANVAS_Y + CANVAS_HEIGHT) {
                        
                        sfVector2i canvas_pos = {mouse_pos.x - CANVAS_X, mouse_pos.y - CANVAS_Y};
                        
                        switch (paint->current_tool) {
                            case TOOL_PENCIL:
                                draw_line(paint, paint->last_mouse_pos, canvas_pos, 
                                         paint->tool_settings.current_color,
                                         paint->tool_settings.pencil_thickness);
                                break;
                            case TOOL_ERASER:
                                draw_line(paint, paint->last_mouse_pos, canvas_pos,
                                         create_color(255, 255, 255, 255),
                                         paint->tool_settings.eraser_size);
                                break;
                            case TOOL_SELECTION:
                                update_selection(paint, canvas_pos);
                                break;
                            default:
                                break;
                        }
                        
                        paint->last_mouse_pos = canvas_pos;
                    }
                }
                break;
                
            case sfEvtKeyPressed:
                if (paint->event.key.code == sfKeyEscape) {
                    if (paint->selection.active) {
                        paint->selection.active = 0;
                    }
                }
                break;
                
            default:
                break;
        }
    }
}

void update_paint(paint_t *paint)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(paint->window);
    
    for (int i = 0; i < paint->toolbar_button_count; i++) {
        update_button_state(&paint->toolbar_buttons[i], mouse_pos, 
                           paint->event.type == sfEvtMouseButtonPressed);
    }
}

void render_paint(paint_t *paint)
{
    sfRenderWindow_clear(paint->window, sfColor_fromRGB(240, 240, 240));
    
    render_menu_bar(paint);
    render_toolbar(paint);
    
    if (paint->canvas_sprite) {
        sfRenderWindow_drawSprite(paint->window, paint->canvas_sprite, NULL);
    }
    
    render_color_palette(paint);
    render_tool_settings(paint);
    render_status_bar(paint);
    
    if (paint->show_file_dialog)
        render_file_dialog(paint);
    if (paint->show_help_dialog)
        render_help_dialog(paint);
    if (paint->show_about_dialog)
        render_about_dialog(paint);
    
    sfRenderWindow_display(paint->window);
}