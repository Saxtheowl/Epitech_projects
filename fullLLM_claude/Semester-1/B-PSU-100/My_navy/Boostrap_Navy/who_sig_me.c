/*
** EPITECH PROJECT, 2024
** Navy's Bootstrap - Who Sig Me
** File description:
** Display signal name and sender PID for received signals
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int sig, siginfo_t *info, void *context)
{
    (void)context;
    printf("Signal %s received from %d\n", strsignal(sig), info->si_pid);
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    struct sigaction sa;
    int signal_num;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <signal1> [signal2] ...\n", argv[0]);
        return 84;
    }

    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    for (int i = 1; i < argc; i++) {
        signal_num = atoi(argv[i]);
        
        if (sigaction(signal_num, &sa, NULL) == -1) {
            fprintf(stderr, "Unable to handle %s signal\n", strsignal(signal_num));
            continue;
        }
    }

    while (1) {
        pause();
    }

    return 0;
}