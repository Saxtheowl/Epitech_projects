/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Main server function
*/

#include "zappy_server.h"

server_t *g_server = NULL;

static void signal_handler(int sig)
{
    (void)sig;
    if (g_server)
        g_server->running = 0;
}

int main(int argc, char **argv)
{
    server_t server = {0};

    g_server = &server;
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    if (parse_arguments(argc, argv, &server) != 0)
        return 84;
    if (init_server(&server) != 0)
        return 84;
    if (init_world(&server) != 0)
        return 84;
    
    server.running = 1;
    spawn_resources(&server);
    
    if (run_server(&server) != 0) {
        cleanup_server(&server);
        return 84;
    }
    
    cleanup_server(&server);
    return 0;
}