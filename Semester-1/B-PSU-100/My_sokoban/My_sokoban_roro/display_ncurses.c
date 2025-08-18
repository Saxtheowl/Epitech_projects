#include "my_sokoban.h"

int init_ncurses(void)
{
    if (!initscr()) {
        return -1;
    }
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    return 0;
}

void cleanup_ncurses(void)
{
    endwin();
}

void display_map(map_t *map)
{
    int max_y, max_x;
    int start_y, start_x;
    
    if (!map || !map->grid)
        return;
    
    getmaxyx(stdscr, max_y, max_x);
    
    start_y = (max_y - map->height) / 2;
    start_x = (max_x - map->width) / 2;
    
    clear();
    
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (start_y + y >= 0 && start_y + y < max_y &&
                start_x + x >= 0 && start_x + x < max_x) {
                mvaddch(start_y + y, start_x + x, map->grid[y][x]);
            }
        }
    }
    
    refresh();
}

void display_message(char *message)
{
    int max_y, max_x;
    int msg_len;
    int start_y, start_x;
    
    if (!message)
        return;
    
    getmaxyx(stdscr, max_y, max_x);
    msg_len = my_strlen(message);
    
    start_y = max_y / 2;
    start_x = (max_x - msg_len) / 2;
    
    clear();
    
    if (start_x >= 0 && start_y >= 0) {
        mvprintw(start_y, start_x, "%s", message);
    }
    
    refresh();
}

int check_terminal_size(map_t *map)
{
    int max_y, max_x;
    
    if (!map)
        return -1;
    
    getmaxyx(stdscr, max_y, max_x);
    
    if (max_y < map->height || max_x < map->width) {
        display_message("Please enlarge the terminal");
        return -1;
    }
    
    return 0;
}