#include "my_top.h"

const char *LOADAVG_PATH_VAR = LOADAVG_PATH;
const char *MEMINFO_PATH_VAR = MEMINFO_PATH;
const char *STAT_PATH_VAR = STAT_PATH;
const char *UPTIME_PATH_VAR = UPTIME_PATH;

static void init_state(top_state_t *state)
{
    memset(state, 0, sizeof(top_state_t));
    state->refresh_delay = 3.0;
    state->max_frames = -1;
    state->memory_unit = 0;
}

static int main_loop(top_state_t *state)
{
    struct timespec delay;
    int input_result;
    
    delay.tv_sec = (long)state->refresh_delay;
    delay.tv_nsec = (long)((state->refresh_delay - delay.tv_sec) * 1000000000);
    
    while (1) {
        if (read_system_info(&state->system) != 0) {
            return 84;
        }
        
        state->process_count = read_processes(state->processes, 
                                            strlen(state->filter_user) ? state->filter_user : NULL);
        if (state->process_count < 0) {
            return 84;
        }
        
        sort_processes_by_pid(state->processes, state->process_count);
        
        clear();
        display_system_info(&state->system, state->memory_unit);
        display_header();
        display_processes(state->processes, state->process_count, 
                         state->selected_line, state->scroll_offset);
        refresh();
        
        state->frame_count++;
        if (state->max_frames > 0 && state->frame_count >= state->max_frames) {
            break;
        }
        
        timeout(delay.tv_sec * 1000 + delay.tv_nsec / 1000000);
        input_result = handle_input(state);
        if (input_result == -1) {
            break;
        }
        if (input_result == -2) {
            return 84;
        }
    }
    
    return 0;
}

int main(int argc, char **argv)
{
    top_state_t state;
    int result;
    
    init_state(&state);
    
    if (parse_args(argc, argv, &state) != 0) {
        return 84;
    }
    
    init_ncurses_display();
    signal(SIGWINCH, handle_resize);
    
    result = main_loop(&state);
    
    cleanup_ncurses_display();
    return result;
}