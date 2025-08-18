#ifndef MY_TOP_H
#define MY_TOP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

#define PROC_DIR "/proc"
#define STAT_FILE "/proc/stat"
#define MEMINFO_FILE "/proc/meminfo"
#define LOADAVG_FILE "/proc/loadavg"
#define UPTIME_FILE "/proc/uptime"

typedef struct process_s {
    int pid;
    char user[32];
    int priority;
    int nice;
    unsigned long virt;
    unsigned long res;
    unsigned long shr;
    char state;
    double cpu_percent;
    double mem_percent;
    unsigned long time;
    char command[256];
    struct process_s *next;
} process_t;

typedef struct system_info_s {
    float loadavg[3];
    unsigned long uptime;
    int users;
    int total_tasks;
    int running_tasks;
    int sleeping_tasks;
    int stopped_tasks;
    int zombie_tasks;
    unsigned long total_mem;
    unsigned long free_mem;
    unsigned long used_mem;
    unsigned long buffers;
    unsigned long cached;
    unsigned long total_swap;
    unsigned long free_swap;
    unsigned long used_swap;
} system_info_t;

typedef struct options_s {
    char *username;
    double delay;
    int frames;
    int current_frame;
} options_t;

int my_strlen(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_atoi(char *str);
double my_atof(char *str);

options_t *parse_options(int ac, char **av);
void free_options(options_t *opts);

system_info_t *get_system_info(void);
process_t *get_processes(char *username_filter);
void free_processes(process_t *list);

void display_system_info(system_info_t *sys);
void display_processes(process_t *list);
void display_top(system_info_t *sys, process_t *list);

void print_usage(void);
int main(int ac, char **av);

#endif