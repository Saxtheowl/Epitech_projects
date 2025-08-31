/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Process information collection
*/

#include "../include/my_top.h"

static int read_stat_file(pid_t pid, process_t *proc)
{
    char path[256];
    FILE *file;
    char state;
    unsigned long utime, stime, vsize, rss;
    int priority, nice;

    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    file = fopen(path, "r");
    if (!file)
        return -1;
    if (fscanf(file, "%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u "
        "%lu %lu %*d %*d %d %d %*d %*d %*u %lu %lu",
        &state, &utime, &stime, &priority, &nice, &vsize, &rss) < 7) {
        fclose(file);
        return -1;
    }
    fclose(file);
    proc->state = state;
    proc->utime = utime;
    proc->stime = stime;
    proc->priority = priority;
    proc->nice = nice;
    proc->virt = vsize / 1024;
    proc->res = rss * 4;
    proc->shr = 0;
    proc->cpu_percent = 0.0;
    proc->mem_percent = 0.0;
    return 0;
}

static int read_status_file(pid_t pid, process_t *proc)
{
    char path[256];
    FILE *file;
    char line[256];
    uid_t uid = 0;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    file = fopen(path, "r");
    if (!file)
        return -1;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Uid:", 4) == 0) {
            sscanf(line, "Uid: %u", &uid);
            break;
        }
    }
    fclose(file);
    struct passwd *pw = getpwuid(uid);
    if (pw)
        strncpy(proc->user, pw->pw_name, MAX_USERNAME_LEN - 1);
    else
        snprintf(proc->user, MAX_USERNAME_LEN, "%u", uid);
    proc->user[MAX_USERNAME_LEN - 1] = '\0';
    return 0;
}

static int read_comm_file(pid_t pid, process_t *proc)
{
    char path[256];
    FILE *file;

    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    file = fopen(path, "r");
    if (!file)
        return -1;
    if (fgets(proc->command, MAX_COMMAND_LEN, file)) {
        char *newline = strchr(proc->command, '\n');
        if (newline)
            *newline = '\0';
    }
    fclose(file);
    return 0;
}

static int should_include_process(process_t *proc, const char *filter_user)
{
    if (!filter_user)
        return 1;
    return strcmp(proc->user, filter_user) == 0;
}

static void count_task_states(top_state_t *state)
{
    int i;

    state->system_info.tasks_total = state->process_count;
    state->system_info.tasks_running = 0;
    state->system_info.tasks_sleeping = 0;
    state->system_info.tasks_stopped = 0;
    state->system_info.tasks_zombie = 0;
    for (i = 0; i < state->process_count; i++) {
        switch (state->processes[i].state) {
        case 'R':
            state->system_info.tasks_running++;
            break;
        case 'S':
        case 'D':
            state->system_info.tasks_sleeping++;
            break;
        case 'T':
            state->system_info.tasks_stopped++;
            break;
        case 'Z':
            state->system_info.tasks_zombie++;
            break;
        }
    }
}

int collect_processes(top_state_t *state)
{
    DIR *proc_dir;
    struct dirent *entry;
    pid_t pid;
    process_t temp_proc;
    int count = 0;

    proc_dir = opendir("/proc");
    if (!proc_dir)
        return -1;
    while ((entry = readdir(proc_dir)) && count < MAX_PROCESSES) {
        pid = atoi(entry->d_name);
        if (pid <= 0)
            continue;
        temp_proc.pid = pid;
        if (read_stat_file(pid, &temp_proc) == -1)
            continue;
        if (read_status_file(pid, &temp_proc) == -1)
            continue;
        if (read_comm_file(pid, &temp_proc) == -1)
            continue;
        if (should_include_process(&temp_proc, state->filter_user))
            state->processes[count++] = temp_proc;
    }
    closedir(proc_dir);
    state->process_count = count;
    count_task_states(state);
    return 0;
}