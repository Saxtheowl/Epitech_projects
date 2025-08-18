#include "my_top.h"

void print_usage(void)
{
    printf("Usage: my_top [-U username] [-d delay] [-n frames]\n");
    printf("  -U username: filter by username\n");
    printf("  -d delay: delay between refreshes (default: 3.0)\n");
    printf("  -n frames: number of frames to show (default: unlimited)\n");
}

int main(int ac, char **av)
{
    options_t *opts;
    system_info_t *sys;
    process_t *processes;
    
    opts = parse_options(ac, av);
    if (!opts) {
        print_usage();
        return 84;
    }
    
    printf("My_Top - Simple Process Monitor\n");
    printf("Press Ctrl+C to exit\n\n");
    
    while (opts->frames == -1 || opts->current_frame < opts->frames) {
        sys = get_system_info();
        processes = get_processes(opts->username);
        
        if (sys && processes) {
            printf("\033[2J\033[H");
            display_top(sys, processes);
        }
        
        free(sys);
        free_processes(processes);
        
        if (opts->frames != -1) {
            opts->current_frame++;
            if (opts->current_frame >= opts->frames)
                break;
        }
        
        usleep((unsigned int)(opts->delay * 1000000));
    }
    
    free_options(opts);
    return 0;
}