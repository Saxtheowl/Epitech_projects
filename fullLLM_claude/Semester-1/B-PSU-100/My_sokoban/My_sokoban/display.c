#include "sokoban.h"

static int term_too_small = 0;

void handle_resize(int sig)
{
    (void)sig;
    endwin();
    refresh();
    clear();
}

void init_ncurses(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    signal(SIGWINCH, handle_resize);
}

void cleanup_ncurses(void)
{
    endwin();
}

void display_error_message(char const *msg)
{
    int rows, cols;
    int msg_len;
    
    getmaxyx(stdscr, rows, cols);
    msg_len = my_strlen(msg);
    
    clear();
    mvprintw(rows / 2, (cols - msg_len) / 2, "%s", msg);
    refresh();
}

void display_map(sokoban_map_t *map)
{
    int rows, cols;
    int i, j;
    int start_row, start_col;
    
    if (!map || !map->map)
        return;
    
    getmaxyx(stdscr, rows, cols);
    
    if (rows < map->height || cols < map->width) {
        display_error_message("Please enlarge your terminal");
        term_too_small = 1;
        return;
    }
    
    term_too_small = 0;
    clear();
    
    start_row = (rows - map->height) / 2;
    start_col = (cols - map->width) / 2;
    
    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            char c = map->map[i][j];
            mvaddch(start_row + i, start_col + j, c);
        }
    }
    
    refresh();
}

int handle_input(void)
{
    int ch = getch();
    
    switch (ch) {
        case KEY_UP:
            return 1;
        case KEY_DOWN:
            return 2;
        case KEY_LEFT:
            return 3;
        case KEY_RIGHT:
            return 4;
        case ' ':
            return 5;
        case 'q':
        case 'Q':
            return -1;
        default:
            return 0;
    }
}