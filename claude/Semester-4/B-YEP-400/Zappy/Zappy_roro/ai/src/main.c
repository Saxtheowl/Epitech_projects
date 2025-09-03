/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** Main AI client function
*/

#include "zappy_ai.h"

ai_t *g_ai = NULL;

static void signal_handler(int sig)
{
    (void)sig;
    if (g_ai)
        g_ai->running = 0;
}

int main(int argc, char **argv)
{
    ai_t ai = {0};

    g_ai = &ai;
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (parse_arguments(argc, argv, &ai) != 0)
        return 84;
    if (connect_to_server(&ai) != 0)
        return 84;
    
    ai.running = 1;
    
    if (run_ai(&ai) != 0) {
        cleanup_ai(&ai);
        return 84;
    }
    
    cleanup_ai(&ai);
    return 0;
}