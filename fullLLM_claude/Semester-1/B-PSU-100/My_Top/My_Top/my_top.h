#ifndef MY_TOP_H
#define MY_TOP_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>

#define MAX_PROCS 1024
#define MAX_LINE 256
#define PROC_PATH "/proc"
#define LOADAVG_PATH "/proc/loadavg"
#define MEMINFO_PATH "/proc/meminfo"
#define STAT_PATH "/proc/stat"
#define UPTIME_PATH "/proc/uptime"

typedef struct {
    double loadavg[3];
    unsigned long uptime_sec;
    int users_count;
    int tasks_total;
    int tasks_running;
    int tasks_sleeping;
    int tasks_stopped;
    int tasks_zombie;
    unsigned long mem_total;
    unsigned long mem_free;
    unsigned long mem_available;
    unsigned long mem_used;
    unsigned long swap_total;
    unsigned long swap_free;
    unsigned long swap_used;
} system_info_t;

typedef struct {
    int pid;
    char user[32];
    int priority;
    int nice;
    unsigned long virt;
    unsigned long res;
    unsigned long shr;
    char status;
    double cpu_percent;
    double mem_percent;
    unsigned long time_total;
    char command[256];
} process_t;

typedef struct {
    system_info_t system;
    process_t processes[MAX_PROCS];
    int process_count;
    int selected_line;
    int scroll_offset;
    char filter_user[32];
    double refresh_delay;
    int frame_count;
    int max_frames;
    int memory_unit;
} top_state_t;

extern const char *LOADAVG_PATH_VAR;
extern const char *MEMINFO_PATH_VAR;
extern const char *STAT_PATH_VAR;
extern const char *UPTIME_PATH_VAR;

int read_system_info(system_info_t *info);
int read_processes(process_t *processes, const char *filter_user);
void sort_processes_by_pid(process_t *processes, int count);

void init_ncurses_display(void);
void cleanup_ncurses_display(void);
void display_system_info(const system_info_t *info, int memory_unit);
void display_processes(const process_t *processes, int count, int selected, int offset);
void display_header(void);

int handle_input(top_state_t *state);
void handle_resize(int sig);

int parse_args(int argc, char **argv, top_state_t *state);
void print_usage(void);

char *format_memory(unsigned long bytes, int unit);
char *format_time(unsigned long seconds);
const char *get_memory_unit_string(int unit);

#endif