/*
** EPITECH PROJECT, 2024
** My_navy
** File description:
** Signal handling for inter-process communication
*/

#include "../include/my_navy.h"

void signal_handler(int sig)
{
    static int bit_count = 0;
    static int current_byte = 0;
    static int data_bytes[2] = {0};
    static int byte_index = 0;

    if (sig == SIGUSR1)
        current_byte |= (1 << bit_count);
    bit_count++;
    if (bit_count == 8) {
        data_bytes[byte_index] = current_byte;
        byte_index++;
        if (byte_index == 2) {
            g_game->attack_x = data_bytes[0];
            g_game->attack_y = data_bytes[1];
            g_game->result_received = 1;
            byte_index = 0;
        }
        bit_count = 0;
        current_byte = 0;
    }
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

void send_position(pid_t pid, int x, int y)
{
    int data[2] = {x, y};
    int i, j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            if (data[i] & (1 << j))
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(1000);
        }
    }
}

int receive_position(void)
{
    g_game->result_received = 0;
    while (!g_game->result_received) {
        pause();
    }
    return 0;
}