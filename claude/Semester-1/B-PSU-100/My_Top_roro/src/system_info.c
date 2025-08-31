/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** System information collection
*/

#include "../include/my_top.h"

static int read_loadavg(double *loadavg)
{
    FILE *file = fopen("/proc/loadavg", "r");

    if (!file)
        return -1;
    if (fscanf(file, "%lf %lf %lf", &loadavg[0], &loadavg[1], &loadavg[2]) != 3) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}

static int read_uptime(double *uptime)
{
    FILE *file = fopen("/proc/uptime", "r");

    if (!file)
        return -1;
    if (fscanf(file, "%lf", uptime) != 1) {
        fclose(file);
        return -1;
    }
    fclose(file);
    return 0;
}

static int count_users(void)
{
    FILE *file = fopen("/proc/loadavg", "r");
    int users = 1;

    if (file) {
        fclose(file);
    }
    return users;
}

static int read_meminfo(system_info_t *info)
{
    FILE *file = fopen("/proc/meminfo", "r");
    char line[256];

    if (!file)
        return -1;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "MemTotal:", 9) == 0)
            sscanf(line, "MemTotal: %lu kB", &info->mem_total);
        else if (strncmp(line, "MemFree:", 8) == 0)
            sscanf(line, "MemFree: %lu kB", &info->mem_free);
        else if (strncmp(line, "Buffers:", 8) == 0)
            sscanf(line, "Buffers: %lu kB", &info->mem_buffers);
        else if (strncmp(line, "SwapTotal:", 10) == 0)
            sscanf(line, "SwapTotal: %lu kB", &info->swap_total);
        else if (strncmp(line, "SwapFree:", 9) == 0)
            sscanf(line, "SwapFree: %lu kB", &info->swap_free);
    }
    fclose(file);
    info->mem_used = info->mem_total - info->mem_free;
    info->swap_used = info->swap_total - info->swap_free;
    return 0;
}

int collect_system_info(system_info_t *info)
{
    if (read_uptime(&info->uptime) == -1)
        return -1;
    if (read_loadavg(info->loadavg) == -1)
        return -1;
    info->users = count_users();
    if (read_meminfo(info) == -1)
        return -1;
    return 0;
}