/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Main loop and ncurses management
*/

#include "../include/my_top.h"

void init_ncurses(void)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
}

void cleanup_ncurses(void)
{
    endwin();
}

static void refresh_data(top_state_t *state)
{
    collect_system_info(&state->system_info);
    collect_processes(state);
}

void main_loop(top_state_t *state)
{
    int key;
    clock_t start_time, current_time;
    double elapsed;

    start_time = clock();
    while (state->running) {
        clear();
        refresh_data(state);
        display_system_info(state);
        display_processes(state);
        refresh();
        state->current_frame++;
        if (state->max_frames != -1 && state->current_frame >= state->max_frames) {
            state->running = 0;
            break;
        }
        current_time = clock();
        elapsed = 0.0;
        while (elapsed < state->delay && state->running) {
            key = getch();
            if (key != ERR) {
                handle_input(state, key);
            }
            usleep(10000);
            current_time = clock();
            elapsed = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;
        }
        start_time = clock();
    }
}