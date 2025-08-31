/*
** EPITECH PROJECT, 2024
** My_sokoban
** File description:
** NCurses utility functions for my_sokoban
*/

#include "../include/my_sokoban.h"

void setup_ncurses(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);
}

void cleanup_ncurses(void)
{
    endwin();
}