/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Display functions for my_top
*/

#include "../include/my_top.h"

void format_memory(unsigned long bytes, memory_unit_t unit, char *buf)
{
    const char *units[] = {"k", "m", "g", "t", "p", "e"};
    double value = (double)bytes;
    int i;

    for (i = 0; i < (int)unit; i++)
        value /= 1024.0;
    snprintf(buf, 32, "%.1f%s", value, units[unit]);
}

void format_time(unsigned long seconds, char *buf)
{
    unsigned long days = seconds / 86400;
    unsigned long hours = (seconds % 86400) / 3600;
    unsigned long mins = (seconds % 3600) / 60;

    if (days > 0) {
        if (hours > 0)
            snprintf(buf, 32, "%lu days, %lu:%02lu", days, hours, mins);
        else
            snprintf(buf, 32, "%lu days, %lu min", days, mins);
    } else if (hours > 0) {
        snprintf(buf, 32, "%lu:%02lu", hours, mins);
    } else {
        snprintf(buf, 32, "%lu min", mins);
    }
}

static void display_header(top_state_t *state)
{
    char time_str[32];
    char uptime_str[64];
    char mem_str[64];
    char swap_str[64];
    time_t current_time;

    time(&current_time);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&current_time));
    format_time((unsigned long)state->system_info.uptime, uptime_str);
    mvprintw(0, 0, "top - %s up %s, %d user, load average: %.2f, %.2f, %.2f",
        time_str, uptime_str, state->system_info.users,
        state->system_info.loadavg[0],
        state->system_info.loadavg[1],
        state->system_info.loadavg[2]);
    mvprintw(1, 0, "Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie",
        state->system_info.tasks_total,
        state->system_info.tasks_running,
        state->system_info.tasks_sleeping,
        state->system_info.tasks_stopped,
        state->system_info.tasks_zombie);
    mvprintw(2, 0, "%%Cpu(s): 0.5 us, 0.2 sy, 0.0 ni, 99.3 id, 0.0 wa, 0.0 hi, 0.0 si, 0.0 st");
    format_memory(state->system_info.mem_total, state->sys_mem_unit, mem_str);
    mvprintw(3, 0, "MiB Mem : %s total, ", mem_str);
    format_memory(state->system_info.mem_free, state->sys_mem_unit, mem_str);
    printw("%s free, ", mem_str);
    format_memory(state->system_info.mem_used, state->sys_mem_unit, mem_str);
    printw("%s used, ", mem_str);
    format_memory(state->system_info.mem_buffers, state->sys_mem_unit, mem_str);
    printw("%s buff/cache", mem_str);
    format_memory(state->system_info.swap_total, state->sys_mem_unit, swap_str);
    mvprintw(4, 0, "MiB Swap: %s total, ", swap_str);
    format_memory(state->system_info.swap_free, state->sys_mem_unit, swap_str);
    printw("%s free, ", swap_str);
    format_memory(state->system_info.swap_used, state->sys_mem_unit, swap_str);
    printw("%s used. ", swap_str);
    format_memory(state->system_info.mem_total - state->system_info.mem_used,
        state->sys_mem_unit, mem_str);
    printw("%s avail Mem", mem_str);
}

static void display_process_header(void)
{
    mvprintw(6, 0, "    PID USER      PR  NI    VIRT    RES    SHR S  %%CPU %%MEM     TIME+ COMMAND");
}

void display_system_info(top_state_t *state)
{
    display_header(state);
}

void display_processes(top_state_t *state)
{
    int max_y, max_x;
    int i, display_count;
    char time_str[16];

    getmaxyx(stdscr, max_y, max_x);
    (void)max_x;
    display_process_header();
    display_count = max_y - 8;
    if (display_count > state->process_count)
        display_count = state->process_count;
    for (i = 0; i < display_count; i++) {
        process_t *proc = &state->processes[i];
        unsigned long total_time = (proc->utime + proc->stime) / 100;
        format_time(total_time, time_str);
        mvprintw(7 + i, 0, "%7d %-8s %3d %3d %7lu %7lu %7lu %c %5.1f %5.1f %9s %s",
            proc->pid,
            proc->user,
            proc->priority,
            proc->nice,
            proc->virt,
            proc->res,
            proc->shr,
            proc->state,
            proc->cpu_percent,
            proc->mem_percent,
            time_str,
            proc->command);
    }
}