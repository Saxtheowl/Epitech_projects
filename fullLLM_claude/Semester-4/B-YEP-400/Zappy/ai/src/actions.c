/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Game action implementations
*/

#include "ai.h"

void move_forward(ai_client_t *ai)
{
    send_command(ai, "Forward");
}

void turn_left(ai_client_t *ai)
{
    send_command(ai, "Left");
    ai->orientation--;
    if (ai->orientation < ORIENTATION_NORTH) {
        ai->orientation = ORIENTATION_WEST;
    }
}

void turn_right(ai_client_t *ai)
{
    send_command(ai, "Right");
    ai->orientation++;
    if (ai->orientation > ORIENTATION_WEST) {
        ai->orientation = ORIENTATION_NORTH;
    }
}

void look_around(ai_client_t *ai)
{
    send_command(ai, "Look");
}

void take_object(ai_client_t *ai, const char *object)
{
    char command[64];
    snprintf(command, sizeof(command), "Take %s", object);
    send_command(ai, command);
}

void set_object(ai_client_t *ai, const char *object)
{
    char command[64];
    snprintf(command, sizeof(command), "Set %s", object);
    send_command(ai, command);
}

void broadcast_message(ai_client_t *ai, const char *message)
{
    char command[256];
    snprintf(command, sizeof(command), "Broadcast %s", message);
    send_command(ai, command);
}

void check_inventory(ai_client_t *ai)
{
    send_command(ai, "Inventory");
}

void start_incantation(ai_client_t *ai)
{
    send_command(ai, "Incantation");
}

void parse_inventory_response(ai_client_t *ai, const char *response)
{
    // Parse response like "[ food 5, linemate 2, deraumere 1, ... ]"
    memset(ai->inventory, 0, sizeof(ai->inventory));

    char *copy = strdup(response);
    char *token = strtok(copy, " ,[]");

    while (token != NULL) {
        if (strcmp(token, "food") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_FOOD] = atoi(token);
        } else if (strcmp(token, "linemate") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_LINEMATE] = atoi(token);
        } else if (strcmp(token, "deraumere") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_DERAUMERE] = atoi(token);
        } else if (strcmp(token, "sibur") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_SIBUR] = atoi(token);
        } else if (strcmp(token, "mendiane") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_MENDIANE] = atoi(token);
        } else if (strcmp(token, "phiras") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_PHIRAS] = atoi(token);
        } else if (strcmp(token, "thystame") == 0) {
            token = strtok(NULL, " ,[]");
            if (token) ai->inventory[RESOURCE_THYSTAME] = atoi(token);
        }
        token = strtok(NULL, " ,[]");
    }

    free(copy);
}

void parse_look_response(ai_client_t *ai, const char *response)
{
    // Parse look response like "[ player food linemate ]"
    // For now, just check if there are resources on current tile

    if (strstr(response, "food")) {
        take_object(ai, "food");
    }

    if (strstr(response, "linemate")) {
        take_object(ai, "linemate");
    }

    if (strstr(response, "deraumere")) {
        take_object(ai, "deraumere");
    }

    if (strstr(response, "sibur")) {
        take_object(ai, "sibur");
    }

    if (strstr(response, "mendiane")) {
        take_object(ai, "mendiane");
    }

    if (strstr(response, "phiras")) {
        take_object(ai, "phiras");
    }

    if (strstr(response, "thystame")) {
        take_object(ai, "thystame");
    }
}