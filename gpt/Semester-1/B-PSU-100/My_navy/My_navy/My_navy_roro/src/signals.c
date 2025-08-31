/*
** EPITECH PROJECT, 2025
** My_navy_roro
** File description:
** Connection and signaling
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "navy.h"

static volatile sig_atomic_t g_count = 0;
static volatile sig_atomic_t g_edge = 0;
static volatile sig_atomic_t g_connected = 0;
static volatile sig_atomic_t g_last_sig = 0;

static void handler(int sig, siginfo_t *info, void *u)
{
    (void)u;
    g_last_sig = sig;
    if (!g_connected && info && info->si_pid > 0)
        g_connected = info->si_pid;
    if (sig == SIGUSR1) {
        g_count += 1;
    } else if (sig == SIGUSR2) {
        g_edge = 1;
    }
}

static void setup_handlers(void)
{
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

int start_connection(game_t *g, const char *pid_arg)
{
    g->self_pid = getpid();
    g->enemy_pid = 0;
    g->is_player2 = 0;
    setup_handlers();
    if (pid_arg == NULL) {
        printf("my_pid: %d\n\nwaiting for enemy...\n\n", (int)g->self_pid);
        while (!g_connected)
            pause();
        g->enemy_pid = (pid_t)g_connected;
        printf("enemy connected\n\n");
    } else {
        int pid = 0;
        for (int i = 0; pid_arg[i]; ++i) pid = pid * 10 + (pid_arg[i] - '0');
        g->enemy_pid = (pid_t)pid;
        g->is_player2 = 1;
        printf("my_pid: %d\n\n", (int)g->self_pid);
        kill(g->enemy_pid, SIGUSR2);
        printf("successfully connected to enemy\n\n");
    }
    return 0;
}

static void send_value(pid_t dst, int v)
{
    int i;

    for (i = 0; i < v; ++i) {
        kill(dst, SIGUSR1);
        usleep(5000);
    }
    kill(dst, SIGUSR2);
}

static int recv_value(void)
{
    g_count = 0;
    g_edge = 0;
    while (!g_edge)
        pause();
    g_edge = 0;
    return (int)g_count;
}

static int coord_to_val(const char *s)
{
    int c = s[0] - 'A';
    int r = s[1] - '1';
    return r * 8 + c + 1;
}

static void val_to_coord(int v, int *r, int *c)
{
    v -= 1;
    *r = v / 8;
    *c = v % 8;
}

static int apply_attack(board_t *b, int r, int c)
{
    char *cell = &b->cells[r][c];
    if (*cell == '.' || *cell == 'o' || *cell == 'x') {
        *cell = 'o';
        return 0;
    }
    *cell = 'x';
    return 1;
}

int run_game(game_t *g)
{
    char buf[16];

    print_boards(g);
    g->my_hits = 0;
    g->enemy_hits = 0;
    while (1) {
        if (!g->is_player2) {
            int v;
            int r;
            int c;
            int hit;

            printf("\nattack: ");
            fflush(stdout);
            if (!fgets(buf, sizeof(buf), stdin))
                return 0;
            if (!(buf[0] >= 'A' && buf[0] <= 'H' && buf[1] >= '1' && buf[1] <= '8'))
                continue;
            v = coord_to_val(buf);
            send_value(g->enemy_pid, v);
            pause();
            if (g_last_sig == SIGUSR1) hit = 1; else hit = 0;
            printf("\nresult: %c%c:%s\n\n", buf[0], buf[1], hit ? "hit" : "missed");
            val_to_coord(v, &r, &c);
            g->enemy.cells[r][c] = hit ? 'x' : 'o';
            if (hit)
                g->my_hits += 1;
            if (g->my_hits >= TOTAL_SHIP_CELLS) {
                print_boards(g);
                printf("\nI won\n");
                return 0;
            }
            print_boards(g);
        } else {
            int v = recv_value();
            int r;
            int c;
            int hit;

            val_to_coord(v, &r, &c);
            hit = apply_attack(&g->my, r, c);
            kill(g->enemy_pid, hit ? SIGUSR1 : SIGUSR2);
            printf("\nwaiting for enemy's attack...\n\n");
            print_boards(g);
            if (hit)
                g->enemy_hits += 1;
            if (g->enemy_hits >= TOTAL_SHIP_CELLS) {
                printf("\nEnemy won\n");
                return 1;
            }
        }
        g->is_player2 = !g->is_player2;
    }
    return 0;
}
