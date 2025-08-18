#include "my_top.h"

static int read_file_line(char *filename, char *buffer, int size)
{
    FILE *file;
    
    file = fopen(filename, "r");
    if (!file)
        return -1;
    
    if (!fgets(buffer, size, file)) {
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return 0;
}

static void parse_loadavg(system_info_t *sys)
{
    char buffer[256];
    
    if (read_file_line(LOADAVG_FILE, buffer, sizeof(buffer)) == 0) {
        sscanf(buffer, "%f %f %f", &sys->loadavg[0], &sys->loadavg[1], &sys->loadavg[2]);
    }
}

static void parse_uptime(system_info_t *sys)
{
    char buffer[256];
    
    if (read_file_line(UPTIME_FILE, buffer, sizeof(buffer)) == 0) {
        sscanf(buffer, "%lu", &sys->uptime);
    }
}

static void parse_meminfo(system_info_t *sys)
{
    FILE *file;
    char line[256];
    char key[64];
    unsigned long value;
    
    file = fopen(MEMINFO_FILE, "r");
    if (!file)
        return;
    
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s %lu", key, &value) == 2) {
            if (my_strcmp(key, "MemTotal:") == 0)
                sys->total_mem = value;
            else if (my_strcmp(key, "MemFree:") == 0)
                sys->free_mem = value;
            else if (my_strcmp(key, "Buffers:") == 0)
                sys->buffers = value;
            else if (my_strcmp(key, "Cached:") == 0)
                sys->cached = value;
            else if (my_strcmp(key, "SwapTotal:") == 0)
                sys->total_swap = value;
            else if (my_strcmp(key, "SwapFree:") == 0)
                sys->free_swap = value;
        }
    }
    
    fclose(file);
    
    sys->used_mem = sys->total_mem - sys->free_mem - sys->buffers - sys->cached;
    sys->used_swap = sys->total_swap - sys->free_swap;
}

system_info_t *get_system_info(void)
{
    system_info_t *sys;
    
    sys = malloc(sizeof(system_info_t));
    if (!sys)
        return NULL;
    
    memset(sys, 0, sizeof(system_info_t));
    
    parse_loadavg(sys);
    parse_uptime(sys);
    parse_meminfo(sys);
    
    sys->users = 1;
    sys->total_tasks = 0;
    sys->running_tasks = 0;
    sys->sleeping_tasks = 0;
    sys->stopped_tasks = 0;
    sys->zombie_tasks = 0;
    
    return sys;
}