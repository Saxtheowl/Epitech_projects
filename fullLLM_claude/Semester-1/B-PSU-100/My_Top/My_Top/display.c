#include "my_top.h"

void init_ncurses_display(void)
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

void cleanup_ncurses_display(void)
{
    endwin();
}

void handle_resize(int sig)
{
    (void)sig;
    endwin();
    refresh();
    clear();
}

char *format_memory(unsigned long bytes, int unit)
{
    static char buffer[32];
    const char *units[] = {"KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
    double value = bytes / 1024.0;
    int i;
    
    for (i = 0; i < unit && i < 5; i++) {
        value /= 1024.0;
    }
    
    if (unit >= 6) unit = 5;
    
    snprintf(buffer, sizeof(buffer), "%.1f%s", value, units[unit]);
    return buffer;
}

char *format_time(unsigned long seconds)
{
    static char buffer[64];
    unsigned long days = seconds / 86400;
    unsigned long hours = (seconds % 86400) / 3600;
    unsigned long mins = (seconds % 3600) / 60;
    
    if (days > 0) {
        if (hours > 0)
            snprintf(buffer, sizeof(buffer), "%lu days, %lu:%02lu", days, hours, mins);
        else
            snprintf(buffer, sizeof(buffer), "%lu days, %lu min", days, mins);
    } else if (hours > 0) {
        snprintf(buffer, sizeof(buffer), "%lu:%02lu", hours, mins);
    } else {
        snprintf(buffer, sizeof(buffer), "%lu min", mins);
    }
    
    return buffer;
}

const char *get_memory_unit_string(int unit)
{
    const char *units[] = {"KiB", "MiB", "GiB", "TiB", "PiB", "EiB"};
    if (unit < 0 || unit > 5) unit = 0;
    return units[unit];
}

void display_system_info(const system_info_t *info, int memory_unit)
{
    time_t now;
    struct tm *timeinfo;
    
    time(&now);
    timeinfo = localtime(&now);
    
    mvprintw(0, 0, "top - %02d:%02d:%02d up %s, %d user, load average: %.2f, %.2f, %.2f",
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
             format_time(info->uptime_sec),
             info->users_count,
             info->loadavg[0], info->loadavg[1], info->loadavg[2]);
    
    mvprintw(1, 0, "Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie",
             info->tasks_total, info->tasks_running, info->tasks_sleeping,
             info->tasks_stopped, info->tasks_zombie);
    
    mvprintw(2, 0, "%%Cpu(s): 0.0 us, 0.0 sy, 0.0 ni, 0.0 id, 0.0 wa, 0.0 hi, 0.0 si, 0.0 st");
    
    mvprintw(3, 0, "%s Mem : %s total, %s free, %s used, %s buff/cache",
             get_memory_unit_string(memory_unit),
             format_memory(info->mem_total, memory_unit),
             format_memory(info->mem_free, memory_unit),
             format_memory(info->mem_used, memory_unit),
             format_memory(info->mem_total - info->mem_free - info->mem_used, memory_unit));
    
    mvprintw(4, 0, "%s Swap: %s total, %s free, %s used. %s avail Mem",
             get_memory_unit_string(memory_unit),
             format_memory(info->swap_total, memory_unit),
             format_memory(info->swap_free, memory_unit),
             format_memory(info->swap_used, memory_unit),
             format_memory(info->mem_available, memory_unit));
}

void display_header(void)
{
    mvprintw(6, 0, "    PID USER      PR  NI    VIRT    RES    SHR S  %%CPU %%MEM     TIME+ COMMAND");
}

void display_processes(const process_t *processes, int count, int selected, int offset)
{
    int i, display_count;
    int max_y, max_x;
    
    getmaxyx(stdscr, max_y, max_x);
    (void)max_x;
    
    display_count = max_y - 8;
    if (display_count > count - offset)
        display_count = count - offset;
    
    for (i = 0; i < display_count && (offset + i) < count; i++) {
        const process_t *proc = &processes[offset + i];
        
        if (i == selected - offset) {
            attron(A_REVERSE);
        }
        
        mvprintw(7 + i, 0, "%7d %-8s %3d %3d %7lu %6lu %6lu %c %4.1f %4.1f %8lu %s",
                 proc->pid,
                 proc->user,
                 proc->priority,
                 proc->nice,
                 proc->virt / 1024,
                 proc->res / 1024,
                 proc->shr / 1024,
                 proc->status,
                 proc->cpu_percent,
                 proc->mem_percent,
                 proc->time_total,
                 proc->command);
        
        if (i == selected - offset) {
            attroff(A_REVERSE);
        }
    }
}