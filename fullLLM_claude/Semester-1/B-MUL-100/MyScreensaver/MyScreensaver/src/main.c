/*
** EPITECH PROJECT, 2024
** MyScreensaver
** File description:
** Main function for MyScreensaver project
*/

#include "my_screensaver.h"

int main(int ac, char **av)
{
    screensaver_t screensaver;
    int animation_id = 0;
    int show_descriptions = 0;
    int result;

    if (parse_arguments(ac, av, &animation_id, &show_descriptions) != 0)
        return 84;

    if (show_descriptions) {
        display_descriptions();
        return 0;
    }

    if (animation_id < 1 || animation_id > MAX_ANIMATIONS) {
        fprintf(stderr, "Error: Animation ID must be between 1 and %d\n", MAX_ANIMATIONS);
        return 84;
    }

    srand(time(NULL));

    if (init_screensaver(&screensaver) != 0) {
        fprintf(stderr, "Error: Failed to initialize screensaver\n");
        return 84;
    }

    result = run_screensaver(&screensaver, animation_id);
    cleanup_screensaver(&screensaver);

    return result;
}