/*
** EPITECH PROJECT, 2025
** Zappy AI
** File description:
** AI client header file
*/

#ifndef ZAPPY_AI_H_
    #define ZAPPY_AI_H_

    #define _GNU_SOURCE
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <errno.h>
    #include <signal.h>
    #include <time.h>

    #define BUFFER_SIZE 4096
    #define MAX_INVENTORY 7

    typedef enum resource_type_e {
        FOOD = 0,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME,
        NB_RESOURCES
    } resource_type_t;

    typedef struct ai_s {
        int socket_fd;
        char *server_name;
        int port;
        char *team_name;
        int level;
        int inventory[NB_RESOURCES];
        int x;
        int y;
        int orientation;
        int world_width;
        int world_height;
        int slots_available;
        int running;
    } ai_t;

    int parse_arguments(int argc, char **argv, ai_t *ai);
    void display_help(void);
    int connect_to_server(ai_t *ai);
    int run_ai(ai_t *ai);
    void send_command(ai_t *ai, const char *command);
    char *receive_response(ai_t *ai);
    void process_welcome(ai_t *ai);
    void ai_strategy(ai_t *ai);
    void cleanup_ai(ai_t *ai);
    void look_around(ai_t *ai);
    void take_resources(ai_t *ai);
    void move_randomly(ai_t *ai);
    int can_evolve(ai_t *ai);
    void try_incantation(ai_t *ai);

#endif /* !ZAPPY_AI_H_ */