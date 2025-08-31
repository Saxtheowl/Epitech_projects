/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Input handling for my_top
*/

#include "../include/my_top.h"

void send_signal_prompt(top_state_t *state)
{
    pid_t target_pid;
    int signal_num = SIGTERM;
    char input[32];

    if (state->process_count == 0)
        return;
    target_pid = state->processes[state->selected_process].pid;
    mvprintw(LINES - 2, 0, "PID to signal/kill [default pid = %d]: ", target_pid);
    clrtoeol();
    refresh();
    echo();
    if (getnstr(input, sizeof(input) - 1) == OK && strlen(input) > 0) {
        target_pid = atoi(input);
    }
    mvprintw(LINES - 1, 0, "Send pid %d signal [15/sigterm]: ", target_pid);
    clrtoeol();
    refresh();
    if (getnstr(input, sizeof(input) - 1) == OK && strlen(input) > 0) {
        signal_num = atoi(input);
    }
    noecho();
    kill(target_pid, signal_num);
}

static void cycle_memory_unit(memory_unit_t *unit, int is_system)
{
    *unit = (*unit + 1) % (is_system ? UNIT_MAX : UNIT_PIB);
}

void handle_input(top_state_t *state, int key)
{
    switch (key) {
    case 'q':
    case 'Q':
        state->running = 0;
        break;
    case 'e':
    case 'E':
        cycle_memory_unit(&state->mem_unit, 0);
        break;
    case KEY_UP:
        if (state->selected_process > 0)
            state->selected_process--;
        break;
    case KEY_DOWN:
        if (state->selected_process < state->process_count - 1)
            state->selected_process++;
        break;
    case 'k':
    case 'K':
        send_signal_prompt(state);
        break;
    }
    if (key == 'E' + ('A' - 'a')) {
        cycle_memory_unit(&state->sys_mem_unit, 1);
    }
}