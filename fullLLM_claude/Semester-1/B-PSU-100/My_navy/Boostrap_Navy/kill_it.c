/*
** EPITECH PROJECT, 2024
** Navy's Bootstrap - Kill It
** File description:
** Send SIGQUIT signal to specified PID
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int pid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 84;
    }

    pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID\n");
        return 84;
    }

    if (kill(pid, SIGQUIT) == -1) {
        perror("kill");
        return 84;
    }

    return 0;
}