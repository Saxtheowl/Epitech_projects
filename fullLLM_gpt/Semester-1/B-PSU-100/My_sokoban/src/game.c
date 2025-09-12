#include <string.h>
#include "../include/sok.h"


int step(map_t *m, char mv)
{
    int dx=0, dy=0;
    if (mv=='U') dy=-1; else if (mv=='D') dy=1; else if (mv=='L') dx=-1; else if (mv=='R') dx=1; else return 1;
    int nx=m->px+dx, ny=m->py+dy; if (nx<0||ny<0||nx>=m->w||ny>=m->h) return 1;
    int ni=ny*m->w+nx; char dest=m->cells[ni];
    if (dest=='#') return 1;
    if (dest=='X'){
        int bx=nx+dx, by=ny+dy; if (bx<0||by<0||bx>=m->w||by>=m->h) return 1;
        int bi=by*m->w+bx; char bdest=m->cells[bi];
        if (bdest!=' ') return 1;
        m->cells[bi]='X'; m->cells[ni]=' ';
    }
    m->px=nx; m->py=ny; return 0;
}

int play_script(map_t *m, const char *moves)
{
    if (!moves) return 0;
    for (size_t i=0; moves[i]; ++i){ step(m, moves[i]); if (is_win(m)) break; }
    return 0;
}
