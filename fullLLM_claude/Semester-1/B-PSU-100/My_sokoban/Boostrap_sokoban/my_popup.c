#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int max_y, max_x;
    int y, x;
    int len;
    int ch;

    if (argc != 2) {
        return 84;
    }

    len = strlen(argv[1]);

    initscr();
    noecho();
    cbreak();
    
    getmaxyx(stdscr, max_y, max_x);
    
    y = max_y / 2;
    x = (max_x - len) / 2;
    
    mvprintw(y, x, "%s", argv[1]);
    refresh();
    
    while ((ch = getch()) != ' ') {
        continue;
    }
    
    clear();
    refresh();
    endwin();
    
    return 0;
}