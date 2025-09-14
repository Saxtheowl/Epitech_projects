#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/navy.h"

static int pos_to_xy(const char *s, int *x, int *y)
{
    // Format like A1 .. J10
    if (!isalpha((unsigned char)s[0])) return -1;
    char col = (char)toupper((unsigned char)s[0]);
    if (col < 'A' || col > 'J') return -1;
    int row = 0; if (sscanf(s+1, "%d", &row) != 1) return -1;
    if (row < 1 || row > 10) return -1;
    *x = col - 'A'; *y = row - 1; return 0;
}

int load_map(const char *path, board_t *b)
{
    memset(b->cells, '.', sizeof b->cells);
    b->w = b->h = 10;
    FILE *f = fopen(path, "r"); if (!f) return 84;
    char line[128]; int used[10][10]; memset(used, 0, sizeof used);
    int expected_sizes[] = {2,3,4,5}; int seen[6]={0};
    while (fgets(line, sizeof line, f)) {
        if (line[0]=='\n' || line[0]=='\0') continue;
        int size; char a[8], bpos[8];
        if (sscanf(line, "%d:%7[^:]:%7s", &size, a, bpos) != 3) { fclose(f); return 84; }
        if (size < 2 || size > 5) { fclose(f); return 84; }
        int x1,y1,x2,y2; if (pos_to_xy(a,&x1,&y1)!=0 || pos_to_xy(bpos,&x2,&y2)!=0) { fclose(f); return 84; }
        int dx = (x2>x1) ? 1 : (x2<x1 ? -1 : 0);
        int dy = (y2>y1) ? 1 : (y2<y1 ? -1 : 0);
        if (!((dx==0) ^ (dy==0))) { fclose(f); return 84; }
        int len = (dx!=0) ? (x2-x1)*dx + 1 : (y2-y1)*dy + 1;
        if (len != size) { fclose(f); return 84; }
        for (int i=0;i<size;i++){
            int x=x1 + i*dx, y=y1 + i*dy;
            if (x<0||y<0||x>=10||y>=10) { fclose(f); return 84; }
            if (used[y][x]) { fclose(f); return 84; }
            used[y][x]=1;
            b->cells[y][x] = (char)('0'+size);
        }
        seen[size]++;
    }
    fclose(f);
    // ensure exactly one of each 2,3,4,5
    for (int i=0;i<4;i++){ int s=expected_sizes[i]; if (seen[s]!=1) return 84; }
    return 0;
}

void print_board(const board_t *b)
{
    for (int y=0;y<b->h;y++){
        for (int x=0;x<b->w;x++) putchar(b->cells[y][x]);
        putchar('\n');
    }
}

void print_two_boards(const board_t *mine, const board_t *enemy)
{
    printf("my positions:\n");
    print_board(mine);
    printf("\nenemy's positions:\n");
    print_board(enemy);
}
int parse_coord(const char *s, int *x1b, int *y1b)
{
    int x,y; if (pos_to_xy(s,&x,&y)!=0) return 84; *x1b=x+1; *y1b=y+1; return 0;
}

int board_shot(board_t *b, int x0, int y0)
{
    if (x0<0||y0<0||x0>=b->w||y0>=b->h) return 0;
    char *c=&b->cells[y0][x0];
    if (*c=='x' || *c=='o') return 0;
    if (*c=='2'||*c=='3'||*c=='4'||*c=='5') { *c='x'; return 1; }
    *c='o'; return 0;
}

int my_remaining(board_t *b)
{
    int rem=0; for (int y=0;y<b->h;y++) for (int x=0;x<b->w;x++){
        char c=b->cells[y][x]; if (c=='2'||c=='3'||c=='4'||c=='5') rem++;
    } return rem;
}

void init_enemy(board_t *b)
{
    b->w=b->h=10; for(int y=0;y<10;y++) for(int x=0;x<10;x++) b->cells[y][x]='.';
}
