/*
** EPITECH PROJECT, 2025
** Zappy Server
** File description:
** Main server entry point
*/

#include "server.h"

void print_usage(char *program_name)
{
    printf("USAGE: %s -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\n", program_name);
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution of actions\n");
}

static void signal_handler(int sig)
{
    (void)sig;
    // Handle SIGINT gracefully
}

int main(int argc, char **argv)
{
    server_t server = {0};

    signal(SIGINT, signal_handler);
    signal(SIGPIPE, SIG_IGN);

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-help") == 0)) {
        print_usage(argv[0]);
        return 0;
    }

    if (parse_arguments(argc, argv, &server) != 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 84;
    }

    if (init_server(&server) != 0) {
        fprintf(stderr, "Failed to initialize server\n");
        return 84;
    }

    printf("Zappy server starting on port %d\n", server.port);
    printf("World size: %dx%d\n", server.width, server.height);
    printf("Frequency: %d\n", server.freq);
    printf("Teams: ");
    for (int i = 0; i < server.team_count; i++) {
        printf("%s ", server.teams[i].name);
    }
    printf("\n");

    run_server(&server);
    cleanup_server(&server);

    return 0;
}