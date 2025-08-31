/*
** EPITECH PROJECT, 2024
** MyHunter
** File description:
** Mock main for testing without CSFML
*/

#include <stdio.h>
#include <string.h>

void print_help(void)
{
    printf("USAGE: ./my_hunter [-h]\n");
    printf("Duck Hunt game - Click on ducks to shoot them!\n\n");
    printf("CONTROLS:\n");
    printf("  Mouse click: Shoot\n");
    printf("  ESC: Quit game\n\n");
    printf("OBJECTIVE:\n");
    printf("  Shoot flying ducks to earn points\n");
    printf("  You have limited ammo - make every shot count!\n");
}

static int parse_arguments(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help();
        return 1;
    }
    if (argc > 1) {
        fprintf(stderr, "Invalid arguments. Use -h for help.\n");
        return 84;
    }
    return 0;
}

int my_hunter_mock(void)
{
    printf("MyHunter: Mock version (CSFML not available)\n");
    printf("Game would start here with duck hunting gameplay\n");
    printf("Features implemented:\n");
    printf("- Duck spawning and animation\n");
    printf("- Mouse click collision detection\n");
    printf("- Score and ammo management\n");
    printf("- Game over conditions\n");
    return 0;
}

int main(int argc, char **argv)
{
    int arg_result;

    arg_result = parse_arguments(argc, argv);
    if (arg_result != 0)
        return arg_result;
    return my_hunter_mock();
}