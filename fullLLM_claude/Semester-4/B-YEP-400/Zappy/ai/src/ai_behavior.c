/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** AI behavior and decision making
*/

#include "ai.h"

void run_ai_client(ai_client_t *ai)
{
    char response[BUFFER_SIZE];

    while (ai->connected) {
        update_ai_state(ai);
        execute_ai_action(ai);

        // Receive server response
        if (receive_response(ai, response, sizeof(response)) > 0) {
            handle_server_response(ai, response);
        }

        // Small delay to prevent spam
        usleep(100000); // 100ms
    }
}

void update_ai_state(ai_client_t *ai)
{
    // Check if we need food
    if (ai->inventory[RESOURCE_FOOD] <= 2) {
        ai->state = STATE_COLLECTING;
        return;
    }

    // Check if we can elevate
    if (has_elevation_resources(ai)) {
        ai->state = STATE_SEEKING_ELEVATION;
        return;
    }

    // Default to exploring/collecting
    if (ai->state == STATE_INCANTING) {
        return; // Wait for incantation to complete
    }

    ai->state = STATE_EXPLORING;
}

void execute_ai_action(ai_client_t *ai)
{
    switch (ai->state) {
        case STATE_EXPLORING:
            explore_map(ai);
            break;
        case STATE_COLLECTING:
            collect_resources(ai);
            break;
        case STATE_SEEKING_ELEVATION:
            attempt_elevation(ai);
            break;
        case STATE_INCANTING:
            // Wait for incantation result
            break;
        default:
            explore_map(ai);
            break;
    }
}

void explore_map(ai_client_t *ai)
{
    static int action_counter = 0;

    switch (action_counter % 4) {
        case 0:
            look_around(ai);
            break;
        case 1:
            move_forward(ai);
            break;
        case 2:
            turn_right(ai);
            break;
        case 3:
            move_forward(ai);
            break;
    }

    action_counter++;
}

void collect_resources(ai_client_t *ai)
{
    static int collect_state = 0;

    switch (collect_state % 3) {
        case 0:
            look_around(ai);
            break;
        case 1:
            // Try to take food
            take_object(ai, "food");
            break;
        case 2:
            // Try to take resources for elevation
            if (ai->level == 1) {
                take_object(ai, "linemate");
            } else if (ai->level == 2) {
                take_object(ai, "linemate");
                take_object(ai, "deraumere");
                take_object(ai, "sibur");
            }
            break;
    }

    collect_state++;
}

void attempt_elevation(ai_client_t *ai)
{
    // First, broadcast to gather team members
    broadcast_message(ai, "elevation");

    // Then try incantation
    start_incantation(ai);
    ai->state = STATE_INCANTING;
}

bool has_elevation_resources(ai_client_t *ai)
{
    switch (ai->level) {
        case 1:
            return ai->inventory[RESOURCE_LINEMATE] >= 1;
        case 2:
            return ai->inventory[RESOURCE_LINEMATE] >= 1 &&
                   ai->inventory[RESOURCE_DERAUMERE] >= 1 &&
                   ai->inventory[RESOURCE_SIBUR] >= 1;
        case 3:
            return ai->inventory[RESOURCE_LINEMATE] >= 2 &&
                   ai->inventory[RESOURCE_SIBUR] >= 1 &&
                   ai->inventory[RESOURCE_PHIRAS] >= 2;
        case 4:
            return ai->inventory[RESOURCE_LINEMATE] >= 1 &&
                   ai->inventory[RESOURCE_DERAUMERE] >= 1 &&
                   ai->inventory[RESOURCE_SIBUR] >= 2 &&
                   ai->inventory[RESOURCE_PHIRAS] >= 1;
        case 5:
            return ai->inventory[RESOURCE_LINEMATE] >= 1 &&
                   ai->inventory[RESOURCE_DERAUMERE] >= 2 &&
                   ai->inventory[RESOURCE_SIBUR] >= 1 &&
                   ai->inventory[RESOURCE_MENDIANE] >= 3;
        case 6:
            return ai->inventory[RESOURCE_LINEMATE] >= 1 &&
                   ai->inventory[RESOURCE_DERAUMERE] >= 2 &&
                   ai->inventory[RESOURCE_SIBUR] >= 3 &&
                   ai->inventory[RESOURCE_PHIRAS] >= 1;
        case 7:
            return ai->inventory[RESOURCE_LINEMATE] >= 2 &&
                   ai->inventory[RESOURCE_DERAUMERE] >= 2 &&
                   ai->inventory[RESOURCE_SIBUR] >= 2 &&
                   ai->inventory[RESOURCE_MENDIANE] >= 2 &&
                   ai->inventory[RESOURCE_PHIRAS] >= 2 &&
                   ai->inventory[RESOURCE_THYSTAME] >= 1;
        default:
            return false;
    }
}

void cleanup_ai_client(ai_client_t *ai)
{
    if (ai->socket_fd >= 0) {
        close(ai->socket_fd);
    }
    if (ai->server_ip) {
        free(ai->server_ip);
    }
    if (ai->team_name) {
        free(ai->team_name);
    }
}