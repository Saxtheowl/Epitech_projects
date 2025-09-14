/*
** EPITECH PROJECT, 2024
** MyRadar
** File description:
** Main function for MyRadar project
*/

#include "my_radar.h"

int main(int ac, char **av)
{
    simulation_t sim;
    char *script_path = NULL;
    int result;

    if (parse_arguments(ac, av, &script_path) != 0)
        return 84;

    if (script_path == NULL)
        return 84;

    if (init_simulation(&sim) != 0) {
        fprintf(stderr, "Error: Failed to initialize simulation\n");
        return 84;
    }

    if (parse_script_file(script_path, &sim) != 0) {
        cleanup_simulation(&sim);
        return 84;
    }

    result = run_simulation(&sim);
    cleanup_simulation(&sim);

    return result;
}