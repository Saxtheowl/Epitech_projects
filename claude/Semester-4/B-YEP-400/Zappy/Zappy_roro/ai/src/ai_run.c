/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Main AI loop and execution
*/

#include "zappy_ai.h"

int run_ai(ai_t *ai)
{
    process_welcome(ai);
    
    ai->level = 1;
    ai->orientation = 1;
    memset(ai->inventory, 0, sizeof(ai->inventory));
    ai->inventory[FOOD] = 10;
    
    srand(time(NULL));
    
    while (ai->running) {
        ai_strategy(ai);
    }
    
    return 0;
}

void cleanup_ai(ai_t *ai)
{
    if (ai->socket_fd != -1) {
        close(ai->socket_fd);
        ai->socket_fd = -1;
    }
    
    free(ai->server_name);
    free(ai->team_name);
}