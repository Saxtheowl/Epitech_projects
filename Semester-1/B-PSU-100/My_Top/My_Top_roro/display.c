#include "my_top.h"

static void format_uptime(unsigned long uptime, char *buffer, int size)
{
    unsigned long days = uptime / 86400;
    unsigned long hours = (uptime % 86400) / 3600;
    unsigned long minutes = (uptime % 3600) / 60;
    
    if (days > 0) {
        if (hours > 0)
            snprintf(buffer, size, "%lu days, %lu:%02lu", days, hours, minutes);
        else
            snprintf(buffer, size, "%lu days, %lu min", days, minutes);
    } else if (hours > 0) {
        snprintf(buffer, size, "%lu:%02lu", hours, minutes);
    } else {
        snprintf(buffer, size, "%lu min", minutes);
    }
}

static void format_memory(unsigned long kb, char *buffer, int size)
{
    if (kb >= 1048576) {
        snprintf(buffer, size, "%.1fG", (double)kb / 1048576);
    } else if (kb >= 1024) {
        snprintf(buffer, size, "%.1fM", (double)kb / 1024);
    } else {
        snprintf(buffer, size, "%luK", kb);
    }
}

void display_system_info(system_info_t *sys)
{
    time_t now;
    struct tm *tm_info;
    char time_str[32];
    char uptime_str[64];
    char mem_total[16], mem_free[16], mem_used[16];
    char swap_total[16], swap_free[16], swap_used[16];
    
    time(&now);
    tm_info = localtime(&now);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);
    
    format_uptime(sys->uptime, uptime_str, sizeof(uptime_str));
    format_memory(sys->total_mem, mem_total, sizeof(mem_total));
    format_memory(sys->free_mem, mem_free, sizeof(mem_free));
    format_memory(sys->used_mem, mem_used, sizeof(mem_used));
    format_memory(sys->total_swap, swap_total, sizeof(swap_total));
    format_memory(sys->free_swap, swap_free, sizeof(swap_free));
    format_memory(sys->used_swap, swap_used, sizeof(swap_used));
    
    printf("top - %s up %s, %d user, load average: %.2f, %.2f, %.2f\n",
           time_str, uptime_str, sys->users,
           sys->loadavg[0], sys->loadavg[1], sys->loadavg[2]);
    
    printf("Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie\n",
           sys->total_tasks, sys->running_tasks, sys->sleeping_tasks,
           sys->stopped_tasks, sys->zombie_tasks);
    
    printf("MiB Mem : %s total, %s free, %s used\n",
           mem_total, mem_free, mem_used);
    
    printf("MiB Swap: %s total, %s free, %s used\n",
           swap_total, swap_free, swap_used);
    
    printf("\n");
}

void display_processes(process_t *list)
{
    process_t *current;
    int count = 0;
    
    printf("  PID USER      PR  NI    VIRT    RES    SHR S  %%CPU  %%MEM     TIME+ COMMAND\n");
    
    current = list;
    while (current && count < 20) {
        printf("%5d %-8s %3d %3d %7lu %6lu %6lu %c %5.1f %5.1f %9lu %s\n",
               current->pid, current->user, current->priority, current->nice,
               current->virt, current->res, current->shr, current->state,
               current->cpu_percent, current->mem_percent, current->time,
               current->command);
        current = current->next;
        count++;
    }
}

void display_top(system_info_t *sys, process_t *list)
{
    process_t *current;
    int total = 0, running = 0, sleeping = 0, stopped = 0, zombie = 0;
    
    current = list;
    while (current) {
        total++;
        switch (current->state) {
            case 'R': running++; break;
            case 'S': sleeping++; break;
            case 'T': stopped++; break;
            case 'Z': zombie++; break;
            default: sleeping++; break;
        }
        current = current->next;
    }
    
    sys->total_tasks = total;
    sys->running_tasks = running;
    sys->sleeping_tasks = sleeping;
    sys->stopped_tasks = stopped;
    sys->zombie_tasks = zombie;
    
    display_system_info(sys);
    display_processes(list);
}