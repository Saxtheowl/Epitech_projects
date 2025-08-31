/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Header file for my_top system monitor
*/

#ifndef MY_TOP_H
    #define MY_TOP_H

    #define _GNU_SOURCE

    #include <ncurses.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <dirent.h>
    #include <pwd.h>
    #include <signal.h>
    #include <time.h>
    #include <sys/stat.h>
    #include <sys/sysinfo.h>

    #define MAX_PROCESSES 1000
    #define MAX_COMMAND_LEN 256
    #define MAX_USERNAME_LEN 32
    #define REFRESH_DELAY 3.0

    typedef enum {
        UNIT_KIB = 0,
        UNIT_MIB,
        UNIT_GIB,
        UNIT_TIB,
        UNIT_PIB,
        UNIT_EIB,
        UNIT_MAX
    } memory_unit_t;

    typedef struct process_s {
        pid_t pid;
        char user[MAX_USERNAME_LEN];
        int priority;
        int nice;
        unsigned long virt;
        unsigned long res;
        unsigned long shr;
        char state;
        float cpu_percent;
        float mem_percent;
        unsigned long utime;
        unsigned long stime;
        char command[MAX_COMMAND_LEN];
    } process_t;

    typedef struct system_info_s {
        double uptime;
        int users;
        double loadavg[3];
        int tasks_total;
        int tasks_running;
        int tasks_sleeping;
        int tasks_stopped;
        int tasks_zombie;
        unsigned long mem_total;
        unsigned long mem_free;
        unsigned long mem_used;
        unsigned long mem_buffers;
        unsigned long swap_total;
        unsigned long swap_free;
        unsigned long swap_used;
    } system_info_t;

    typedef struct top_state_s {
        process_t processes[MAX_PROCESSES];
        int process_count;
        system_info_t system_info;
        char *filter_user;
        double delay;
        int max_frames;
        int current_frame;
        int selected_process;
        memory_unit_t mem_unit;
        memory_unit_t sys_mem_unit;
        int running;
    } top_state_t;

    int parse_arguments(int argc, char **argv, top_state_t *state);
    void init_ncurses(void);
    void cleanup_ncurses(void);
    void main_loop(top_state_t *state);
    void display_system_info(top_state_t *state);
    void display_processes(top_state_t *state);
    void handle_input(top_state_t *state, int key);
    int collect_system_info(system_info_t *info);
    int collect_processes(top_state_t *state);
    void print_usage(void);
    void format_memory(unsigned long bytes, memory_unit_t unit, char *buf);
    void format_time(unsigned long seconds, char *buf);
    void send_signal_prompt(top_state_t *state);

#endif