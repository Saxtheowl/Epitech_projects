/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Signal handling utilities
*/

#include "ftrace.h"

void handle_signal(int sig)
{
    switch (sig) {
        case SIGINT:
            printf("\nReceived signal SIGINT\n");
            break;
        case SIGTERM:
            printf("Received signal SIGTERM\n");
            break;
        case SIGWINCH:
            printf("Received signal SIGWINCH\n");
            break;
        case SIGCHLD:
            printf("Received signal SIGCHLD\n");
            break;
        default:
            printf("Received signal %d\n", sig);
            break;
    }
}