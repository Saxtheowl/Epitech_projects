/*
** EPITECH PROJECT, 2024
** Navy's Bootstrap - Signal Me
** File description:
** Count SIGUSR1 and SIGUSR2 signals, display summary on SIGQUIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int sigusr1_count = 0;
static int sigusr2_count = 0;

void sigusr1_handler(int sig)
{
    (void)sig;
    sigusr1_count++;
}

void sigusr2_handler(int sig)
{
    (void)sig;
    sigusr2_count++;
}

void sigquit_handler(int sig)
{
    (void)sig;
    printf("SIGUSR1: %d\n", sigusr1_count);
    printf("SIGUSR2: %d\n", sigusr2_count);
    fflush(stdout);
    exit(0);
}

int main(void)
{
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
    signal(SIGQUIT, sigquit_handler);

    while (1) {
        pause();
    }

    return 0;
}