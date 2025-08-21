/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Mock main for testing without CSFML
*/

#include <stdio.h>
#include <string.h>

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
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        display_help();
        return 0;
    }

    printf("MyHunter requires CSFML to run.\n");
    printf("Please install CSFML and compile with the full implementation.\n");
    printf("For help, run: %s -h\n", av[0]);

    return 0;
}