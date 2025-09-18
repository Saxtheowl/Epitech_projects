/*
** EPITECH PROJECT, 2024
** Navy's Bootstrap - Process Info
** File description:
** Display process information: PID, PPID, PGID
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("PGID: %d\n", getpgrp());
    return 0;
}