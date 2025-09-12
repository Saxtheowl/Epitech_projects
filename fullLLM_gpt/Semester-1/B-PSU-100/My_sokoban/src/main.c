#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sok.h"

static void print_usage(const char *p)
{
    fprintf(stderr, "Usage: %s mapfile\n", p);
}

static void render(const map_t *m)
{
    for (int y=0;y<m->h;y++){
        for (int x=0;x<m->w;x++){
            char out=' ';
            if (m->px==x && m->py==y) out='P';
            else {
                char c=m->cells[y*m->w+x];
                if (c=='#'||c=='X') out=c; else if (m->targets[y*m->w+x]) out='O'; else out=' ';
            }
            char ch=out; write_all(1, &ch, 1);
        }
        write_all(1, "\n", 1);
    }
}

int main(int ac, char **av)
{
    if (ac != 2) { print_usage(av[0]); return 84; }
    map_t m; if (load_map(av[1], &m) != 0) return 84;
    const char *moves = getenv("MOVES");
    if (moves && *moves) play_script(&m, moves);
    render(&m);
    free_map(&m);
    return 0;
}
