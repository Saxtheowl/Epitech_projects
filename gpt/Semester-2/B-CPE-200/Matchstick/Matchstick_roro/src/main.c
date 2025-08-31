/*
** EPITECH PROJECT, 2025
** Matchstick
** File description:
** Entry point
*/

#include <stdio.h>
#include <stdlib.h>
#include "matchstick.h"

int main(int argc, char **argv)
{
    int lines;
    int max_remove;
    board_t *b;
    int ret;

    if (!parse_args(argc, argv, &lines, &max_remove))
        return 84;
    b = board_create(lines, max_remove);
    if (!b)
        return 84;
    board_print(b);
    while (!is_finished(b)) {
        ret = player_turn(b);
        if (ret == -1)
            break;
        if (ret == 1) {
            board_print(b);
            if (is_finished(b)) {
                puts("You lost, too bad...");
                board_destroy(b);
                return 1;
            }
            ai_turn(b);
            board_print(b);
            if (is_finished(b)) {
                puts("I lost... snif... but I'll get you next time!!");
                board_destroy(b);
                return 0;
            }
        }
    }
    board_destroy(b);
    return 0;
}

