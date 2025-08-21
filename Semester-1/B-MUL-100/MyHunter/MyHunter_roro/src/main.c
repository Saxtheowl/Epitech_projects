/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Main function for MyHunter game
*/

#include "../include/my_hunter.h"

void display_help(void)
{
    printf("MY HUNTER - The Duck Hunt Legacy\n\n");
    printf("DESCRIPTION:\n");
    printf("    A classic duck hunting game where you shoot ducks that fly across the screen.\n");
    printf("    Click on ducks to shoot them and earn points.\n\n");
    printf("CONTROLS:\n");
    printf("    LEFT CLICK   - Shoot at ducks\n");
    printf("    ESC          - Exit game\n");
    printf("    CLOSE WINDOW - Exit game\n\n");
    printf("GAMEPLAY:\n");
    printf("    - Ducks appear from the sides and fly across the screen\n");
    printf("    - Click on them to shoot and earn points\n");
    printf("    - Try to achieve the highest score possible\n\n");
    printf("SCORING:\n");
    printf("    - Each duck shot: +10 points\n");
    printf("    - Bonus points for consecutive hits\n\n");
}

int main(int ac, char **av)
{
    game_t game;

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        display_help();
        return 0;
    }

    srand(time(NULL));

    if (game_init(&game) != 0) {
        fprintf(stderr, "Error: Failed to initialize game\n");
        return 84;
    }

    game_loop(&game);
    game_cleanup(&game);

    return 0;
}