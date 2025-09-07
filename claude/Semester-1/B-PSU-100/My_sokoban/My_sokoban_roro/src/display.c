/*
** EPITECH PROJECT, 2025
** my_sokoban
** File description:
** Display and ncurses functions
*/

#include "sokoban.h"

void init_display(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
}

void cleanup_display(void)
{
    endwin();
}

void display_map(sokoban_map_t *map)
{
    int term_height, term_width;
    int start_y, start_x;
    
    if (map == NULL)
        return;
    
    clear();
    getmaxyx(stdscr, term_height, term_width);
    
    start_y = (term_height - map->height) / 2;
    start_x = (term_width - map->width) / 2;
    
    if (start_y < 0)
        start_y = 0;
    if (start_x < 0)
        start_x = 0;
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            char c = map->grid[y][x];
            if (y + start_y < term_height && x + start_x < term_width)
                mvaddch(y + start_y, x + start_x, c);
        }
    }
    
    refresh();
}

void display_help(void)
{
    printf("USAGE\n");
    printf("\t./my_sokoban map\n");
    printf("DESCRIPTION\n");
    printf("\tmap\tfile representing the warehouse map, containing '#' for walls,\n");
    printf("\t\t'P' for the player, 'X' for boxes and 'O' for storage locations.\n");
}

void display_resize_message(void)
{
    int term_height, term_width;
    const char *message = "Please enlarge your terminal";
    int msg_len = my_strlen(message);
    
    clear();
    getmaxyx(stdscr, term_height, term_width);
    
    mvprintw(term_height / 2, (term_width - msg_len) / 2, "%s", message);
    refresh();
}

int check_terminal_size(sokoban_map_t *map)
{
    int term_height, term_width;
    
    if (map == NULL)
        return 0;
    
    getmaxyx(stdscr, term_height, term_width);
    
    return (term_height >= map->height && term_width >= map->width);
}

void handle_resize(int sig)
{
    (void)sig;
    endwin();
    refresh();
    clear();
}