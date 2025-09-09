#include "my_top.h"

static int read_loadavg(system_info_t *info)
{
    FILE *fp;
    
    fp = fopen(LOADAVG_PATH_VAR, "r");
    if (!fp)
        return -1;
    
    if (fscanf(fp, "%lf %lf %lf", &info->loadavg[0], &info->loadavg[1], &info->loadavg[2]) != 3) {
        fclose(fp);
        return -1;
    }
    
    fclose(fp);
    return 0;
}

static int read_uptime(system_info_t *info)
{
    FILE *fp;
    double uptime;
    
    fp = fopen(UPTIME_PATH_VAR, "r");
    if (!fp)
        return -1;
    
    if (fscanf(fp, "%lf", &uptime) != 1) {
        fclose(fp);
        return -1;
    }
    
    info->uptime_sec = (unsigned long)uptime;
    fclose(fp);
    return 0;
}

static int read_meminfo(system_info_t *info)
{
    FILE *fp;
    char line[MAX_LINE];
    char key[64];
    unsigned long value;
    
    fp = fopen(MEMINFO_PATH_VAR, "r");
    if (!fp)
        return -1;
    
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%63s %lu kB", key, &value) == 2) {
            if (strcmp(key, "MemTotal:") == 0)
                info->mem_total = value * 1024;
            else if (strcmp(key, "MemFree:") == 0)
                info->mem_free = value * 1024;
            else if (strcmp(key, "MemAvailable:") == 0)
                info->mem_available = value * 1024;
            else if (strcmp(key, "SwapTotal:") == 0)
                info->swap_total = value * 1024;
            else if (strcmp(key, "SwapFree:") == 0)
                info->swap_free = value * 1024;
        }
    }
    
    info->mem_used = info->mem_total - info->mem_available;
    info->swap_used = info->swap_total - info->swap_free;
    
    fclose(fp);
    return 0;
}

static int count_users(void)
{
    return 1;
}

static int read_stat_tasks(system_info_t *info)
{
    DIR *proc_dir;
    struct dirent *entry;
    char stat_path[512];
    FILE *fp;
    char state;
    
    proc_dir = opendir(PROC_PATH);
    if (!proc_dir)
        return -1;
    
    info->tasks_total = 0;
    info->tasks_running = 0;
    info->tasks_sleeping = 0;
    info->tasks_stopped = 0;
    info->tasks_zombie = 0;
    
    while ((entry = readdir(proc_dir)) != NULL) {
        if (strspn(entry->d_name, "0123456789") != strlen(entry->d_name))
            continue;
        
        snprintf(stat_path, sizeof(stat_path), "%s/%s/stat", PROC_PATH, entry->d_name);
        fp = fopen(stat_path, "r");
        if (!fp)
            continue;
        
        if (fscanf(fp, "%*d %*s %c", &state) == 1) {
            info->tasks_total++;
            switch (state) {
                case 'R':
                    info->tasks_running++;
                    break;
                case 'S':
                case 'D':
                    info->tasks_sleeping++;
                    break;
                case 'T':
                    info->tasks_stopped++;
                    break;
                case 'Z':
                    info->tasks_zombie++;
                    break;
            }
        }
        
        fclose(fp);
    }
    
    closedir(proc_dir);
    return 0;
}

int read_system_info(system_info_t *info)
{
    memset(info, 0, sizeof(system_info_t));
    
    if (read_loadavg(info) != 0)
        return -1;
    
    if (read_uptime(info) != 0)
        return -1;
    
    if (read_meminfo(info) != 0)
        return -1;
    
    if (read_stat_tasks(info) != 0)
        return -1;
    
    info->users_count = count_users();
    
    return 0;
}