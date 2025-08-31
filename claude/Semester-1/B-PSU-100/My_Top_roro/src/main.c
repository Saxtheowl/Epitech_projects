/*
** EPITECH PROJECT, 2024
** My_Top
** File description:
** Main function for my_top system monitor
*/

#include "../include/my_top.h"

static void init_state(top_state_t *state)
{
    state->process_count = 0;
    state->filter_user = NULL;
    state->delay = REFRESH_DELAY;
    state->max_frames = -1;
    state->current_frame = 0;
    state->selected_process = 0;
    state->mem_unit = UNIT_KIB;
    state->sys_mem_unit = UNIT_KIB;
    state->running = 1;
    memset(&state->system_info, 0, sizeof(system_info_t));
    memset(state->processes, 0, sizeof(state->processes));
}

int main(int argc, char **argv)
{
    top_state_t state;

    init_state(&state);
    if (parse_arguments(argc, argv, &state) == 84)
        return 84;
    init_ncurses();
    main_loop(&state);
    cleanup_ncurses();
    if (state.filter_user)
        free(state.filter_user);
    return 0;
}