#include "my_top.h"

static void send_signal_prompt(top_state_t *state)
{
    int target_pid;
    int signal_num = SIGTERM;
    char input[32];
    
    if (state->process_count == 0)
        return;
    
    target_pid = state->processes[state->selected_line].pid;
    
    echo();
    curs_set(1);
    
    mvprintw(LINES - 2, 0, "PID to signal/kill [default pid = %d]: ", target_pid);
    refresh();
    
    if (getnstr(input, sizeof(input) - 1) == OK && strlen(input) > 0) {
        target_pid = atoi(input);
    }
    
    mvprintw(LINES - 1, 0, "Send pid %d signal [default = %d]: ", target_pid, signal_num);
    refresh();
    
    if (getnstr(input, sizeof(input) - 1) == OK && strlen(input) > 0) {
        signal_num = atoi(input);
    }
    
    kill(target_pid, signal_num);
    
    noecho();
    curs_set(0);
    
    clear();
}

int handle_input(top_state_t *state)
{
    int ch = getch();
    int max_display_lines;
    
    getmaxyx(stdscr, max_display_lines, max_display_lines);
    max_display_lines -= 8;
    
    switch (ch) {
        case 'q':
        case 'Q':
            return -1;
        
        case KEY_UP:
            if (state->selected_line > 0) {
                state->selected_line--;
                if (state->selected_line < state->scroll_offset) {
                    state->scroll_offset = state->selected_line;
                }
            }
            break;
        
        case KEY_DOWN:
            if (state->selected_line < state->process_count - 1) {
                state->selected_line++;
                if (state->selected_line >= state->scroll_offset + max_display_lines) {
                    state->scroll_offset = state->selected_line - max_display_lines + 1;
                }
            }
            break;
        
        case 'k':
        case 'K':
            send_signal_prompt(state);
            break;
        
        case 'e':
        case 'E':
            state->memory_unit = (state->memory_unit + 1) % 6;
            break;
        
        case ERR:
            break;
        
        default:
            break;
    }
    
    return 0;
}