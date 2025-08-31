/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Event handling functions
*/

#include "../include/my_radar.h"

void handle_events(radar_t *radar)
{
    while (sfRenderWindow_pollEvent(radar->window, &radar->event)) {
        switch (radar->event.type) {
        case sfEvtClosed:
            sfRenderWindow_close(radar->window);
            radar->simulation_running = 0;
            break;
        case sfEvtKeyPressed:
            switch (radar->event.key.code) {
            case sfKeyEscape:
                sfRenderWindow_close(radar->window);
                radar->simulation_running = 0;
                break;
            case sfKeyL:
                radar->show_hitboxes = !radar->show_hitboxes;
                break;
            case sfKeyS:
                radar->show_sprites = !radar->show_sprites;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}