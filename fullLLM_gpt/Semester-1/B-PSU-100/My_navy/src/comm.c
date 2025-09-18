#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

static volatile sig_atomic_t g_peer_pid = 0;
// For legacy async mode (kept minimal); we move to synchronous waits below
static volatile sig_atomic_t g_ack_ready = 0;
static volatile sig_atomic_t g_stage = 0;

static int debug_enabled(void)
{
    const char *e = getenv("NAVY_DEBUG");
    return (e && *e) ? 1 : 0;
}

static void debugf(const char *msg)
{
    if (debug_enabled()) {
        write(2, msg, (unsigned long)strlen(msg));
        write(2, "\n", 1);
    }
}

static int wait_ack_timeout_ms(int ms)
{
    struct timespec ts = {0, 1*1000*1000}; // 1ms
    int steps = ms;
    while (steps-- > 0) {
        if (g_ack_ready) return 0;
        nanosleep(&ts, NULL);
    }
    return -1;
}

// removed unused wait_flag_timeout to satisfy -Werror

static void handler(int sig, siginfo_t *si, void *ucontext) { (void)sig; (void)si; (void)ucontext; }

void setup_signal_handlers(void)
{
    struct sigaction sa; sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = handler; sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    // Block signals to enable synchronous waiting via sigtimedwait
    sigset_t set; sigemptyset(&set); sigaddset(&set, SIGUSR1); sigaddset(&set, SIGUSR2);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

void set_opponent_pid(int pid) { g_peer_pid = pid; }
int get_my_pid(void) { return (int)getpid(); }

int wait_for_connection(void)
{
    // wait for SIGUSR1 from second player, then reply SIGUSR1
    siginfo_t info; sigset_t set; sigemptyset(&set); sigaddset(&set, SIGUSR1); sigaddset(&set, SIGUSR2);
    while (1) {
        int r = sigwaitinfo(&set, &info);
        if (r == SIGUSR1) break;
    }
    int pid = (int)info.si_pid;
    g_peer_pid = pid;
    kill(pid, SIGUSR1);
    return pid;
}

int connect_to_first(int first_pid)
{
    g_peer_pid = first_pid;
    kill(first_pid, SIGUSR1);
    // wait for SIGUSR1 ack
    siginfo_t info; sigset_t set; sigemptyset(&set); sigaddset(&set, SIGUSR1); sigaddset(&set, SIGUSR2);
    while (1) { int r = sigwaitinfo(&set, &info); if (r == SIGUSR1) break; }
    return 0;
}

int send_coord(int pid, int x1based, int y1based)
{
    // Normalize range [1..10]
    if (x1based < 1) x1based = 1; 
    if (x1based > 10) x1based = 10;
    if (y1based < 1) y1based = 1; 
    if (y1based > 10) y1based = 10;
    struct timespec ts = {0, 30*1000*1000};
    for (int i=0;i<x1based;i++) {
        g_ack_ready = 0; g_stage = 3;
        kill(pid, SIGUSR1); nanosleep(&ts, NULL);
        if (wait_ack_timeout_ms(300) != 0) { debugf("send_coord: ACK timeout on X pulse"); }
        g_stage = 0;
    }
    // separator for X end (no ACK expected)
    kill(pid, SIGUSR2); nanosleep(&ts, NULL);
    for (int i=0;i<y1based;i++) {
        g_ack_ready = 0; g_stage = 3;
        kill(pid, SIGUSR1); nanosleep(&ts, NULL);
        if (wait_ack_timeout_ms(300) != 0) { debugf("send_coord: ACK timeout on Y pulse"); }
        g_stage = 0;
    }
    // separator for Y end (no ACK expected)
    kill(pid, SIGUSR2); nanosleep(&ts, NULL);
    return 0;
}

static int recv_pulses_until_sep(int *count, int timeout_ms)
{
    *count = 0;
    sigset_t set; sigemptyset(&set); sigaddset(&set, SIGUSR1); sigaddset(&set, SIGUSR2);
    struct timespec ts; ts.tv_sec = timeout_ms/1000; ts.tv_nsec = (timeout_ms%1000)*1000000L;
    while (1) {
        siginfo_t info; int r = sigtimedwait(&set, &info, &ts);
        if (r == -1) return -1;
        if (r == SIGUSR1) { (*count)++; if (g_peer_pid) kill(g_peer_pid, SIGUSR2); }
        else if (r == SIGUSR2) { return 0; }
    }
}

int recv_coord_blocking(int *x1based, int *y1based)
{
    int cx=0, cy=0;
    if (recv_pulses_until_sep(&cx, 1500) != 0) { debugf("recv_coord: timeout X"); cx = 1; }
    if (recv_pulses_until_sep(&cy, 1500) != 0) { debugf("recv_coord: timeout Y"); cy = 1; }
    if (cx < 1) cx = 1;
    if (cx > 10) cx = 10;
    if (cy < 1) cy = 1;
    if (cy > 10) cy = 10;
    *x1based = cx; *y1based = cy;
    return 0;
}

int send_shot_result(int pid, int hit)
{
    // Send 1 pulse (SIGUSR1) then separator for hit, or only separator for miss
    g_stage = 2;
    struct timespec ts = {0, 30*1000*1000};
    if (hit) {
        g_ack_ready = 0; g_stage = 3;
        kill(pid, SIGUSR1); nanosleep(&ts, NULL);
        if (wait_ack_timeout_ms(300) != 0) { debugf("send_result: ACK timeout on hit pulse"); }
        g_stage = 0;
    }
    // separator, no ACK expected
    kill(pid, SIGUSR2); nanosleep(&ts, NULL);
    g_stage = 0; g_ack_ready = 0;
    return 0;
}

int recv_shot_result_blocking(void)
{
    int cr=0; if (recv_pulses_until_sep(&cr, 1500) != 0) { debugf("recv_result: timeout"); cr = 0; }
    return (cr > 0) ? 1 : 0;
}

void send_turn_done(int pid)
{
    struct timespec ts = {0, 5*1000*1000}; // 5ms
    kill(pid, SIGUSR2);
    nanosleep(&ts, NULL);
}

void wait_turn_done_blocking(void)
{
    // Wait one SIGUSR2 (turn done token)
    sigset_t set; sigemptyset(&set); sigaddset(&set, SIGUSR2);
    siginfo_t info; (void)sigtimedwait(&set, &info, &(struct timespec){.tv_sec=1,.tv_nsec=0});
}
