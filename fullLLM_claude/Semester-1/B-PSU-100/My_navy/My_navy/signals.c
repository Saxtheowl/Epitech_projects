#include "my_navy.h"

volatile int signal_received = 0;
volatile int signal_bit = 0;
volatile int signal_data = 0;

void signal_handler(int sig, siginfo_t *info, void *context)
{
    (void)context;
    
    if (g_game.enemy_pid == 0) {
        g_game.enemy_pid = info->si_pid;
        signal_received = 1;
        return;
    }
    
    if (info->si_pid != g_game.enemy_pid)
        return;
    
    if (sig == SIGUSR1) {
        signal_data = (signal_data << 1) | 0;
    } else if (sig == SIGUSR2) {
        signal_data = (signal_data << 1) | 1;
    }
    
    signal_bit++;
    
    if (signal_bit == 8) {
        signal_received = 1;
    }
}

void setup_signal_handlers(void)
{
    struct sigaction sa;
    
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

int send_byte(int byte, pid_t pid)
{
    int i;
    
    for (i = 7; i >= 0; i--) {
        if ((byte >> i) & 1) {
            if (kill(pid, SIGUSR2) == -1)
                return -1;
        } else {
            if (kill(pid, SIGUSR1) == -1)
                return -1;
        }
        usleep(1000);
    }
    return 0;
}

int receive_byte(void)
{
    signal_received = 0;
    signal_bit = 0;
    signal_data = 0;
    
    while (!signal_received) {
        pause();
    }
    
    return signal_data;
}

int send_coordinates(int x, int y)
{
    if (send_byte(x, g_game.enemy_pid) == -1)
        return -1;
    if (send_byte(y, g_game.enemy_pid) == -1)
        return -1;
    return 0;
}

int receive_coordinates(int *x, int *y)
{
    int rx = receive_byte();
    int ry = receive_byte();
    
    if (rx < 0 || rx >= GRID_SIZE || ry < 0 || ry >= GRID_SIZE)
        return -1;
    
    *x = rx;
    *y = ry;
    return 0;
}

int send_result(int hit)
{
    return send_byte(hit ? 1 : 0, g_game.enemy_pid);
}

int receive_result(void)
{
    return receive_byte();
}