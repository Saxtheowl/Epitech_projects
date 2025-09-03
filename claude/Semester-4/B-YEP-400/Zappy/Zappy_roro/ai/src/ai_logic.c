/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** AI strategy and decision making
*/

#include "zappy_ai.h"

static int resources_needed[][NB_RESOURCES] = {
    {0, 0, 0, 0, 0, 0, 0},
    {10, 1, 0, 0, 0, 0, 0},
    {20, 1, 1, 1, 0, 0, 0},
    {30, 2, 0, 1, 0, 2, 0},
    {40, 1, 1, 2, 0, 1, 0},
    {50, 1, 2, 1, 3, 0, 0},
    {60, 1, 2, 3, 0, 1, 0},
    {70, 2, 2, 2, 2, 2, 1}
};

void look_around(ai_t *ai)
{
    char *response = NULL;
    
    send_command(ai, "Look");
    response = receive_response(ai);
    if (response) {
        free(response);
    }
}

void take_resources(ai_t *ai)
{
    send_command(ai, "Look");
    char *response = receive_response(ai);
    
    if (response && strstr(response, "food")) {
        send_command(ai, "Take food");
        free(receive_response(ai));
        ai->inventory[FOOD]++;
    }
    
    for (int i = 1; i < NB_RESOURCES; i++) {
        char resource_name[20];
        char take_cmd[30];
        
        switch (i) {
            case LINEMATE: strcpy(resource_name, "linemate"); break;
            case DERAUMERE: strcpy(resource_name, "deraumere"); break;
            case SIBUR: strcpy(resource_name, "sibur"); break;
            case MENDIANE: strcpy(resource_name, "mendiane"); break;
            case PHIRAS: strcpy(resource_name, "phiras"); break;
            case THYSTAME: strcpy(resource_name, "thystame"); break;
        }
        
        if (response && strstr(response, resource_name)) {
            snprintf(take_cmd, sizeof(take_cmd), "Take %s", resource_name);
            send_command(ai, take_cmd);
            free(receive_response(ai));
            ai->inventory[i]++;
        }
    }
    
    free(response);
}

void move_randomly(ai_t *ai)
{
    int action = rand() % 3;
    
    switch (action) {
        case 0:
            send_command(ai, "Forward");
            free(receive_response(ai));
            break;
        case 1:
            send_command(ai, "Right");
            free(receive_response(ai));
            ai->orientation = (ai->orientation % 4) + 1;
            break;
        case 2:
            send_command(ai, "Left");
            free(receive_response(ai));
            ai->orientation = ((ai->orientation - 2 + 4) % 4) + 1;
            break;
    }
}

int can_evolve(ai_t *ai)
{
    if (ai->level >= 8)
        return 0;
    
    for (int i = 0; i < NB_RESOURCES; i++) {
        if (ai->inventory[i] < resources_needed[ai->level][i])
            return 0;
    }
    return 1;
}

void try_incantation(ai_t *ai)
{
    char *response = NULL;
    
    if (!can_evolve(ai))
        return;
    
    send_command(ai, "Incantation");
    response = receive_response(ai);
    
    if (response && strstr(response, "ok")) {
        ai->level++;
        for (int i = 0; i < NB_RESOURCES; i++)
            ai->inventory[i] -= resources_needed[ai->level - 1][i];
    }
    
    free(response);
}

void ai_strategy(ai_t *ai)
{
    static int action_counter = 0;
    
    action_counter++;
    
    if (ai->inventory[FOOD] < 5) {
        look_around(ai);
        take_resources(ai);
    } else if (can_evolve(ai)) {
        try_incantation(ai);
    } else if (action_counter % 3 == 0) {
        look_around(ai);
        take_resources(ai);
    } else {
        move_randomly(ai);
    }
    
    usleep(100000);
}