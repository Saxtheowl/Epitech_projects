/*
** EPITECH PROJECT, 2025
** My_navy_roro
** File description:
** Map loading and printing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "navy.h"

static int coord_ok(const char *s)
{
    return (s[0] >= 'A' && s[0] <= 'H' && s[1] >= '1' && s[1] <= '8');
}

/* kept intentionally simple; inlined placement logic in load_map */

int load_map(const char *path, board_t *b)
{
    FILE *fp;
    char line[64];
    int used[10];
    int i;

    for (i = 0; i < 8; ++i) {
        int j;
        for (j = 0; j < 8; ++j)
            b->cells[i][j] = '.';
    }
    for (i = 0; i < 10; ++i)
        used[i] = 0;
    fp = fopen(path, "r");
    if (!fp)
        return -1;
    for (i = 0; i < 4; ++i) {
        int size;
        int c1;
        int r1;
        int c2;
        int r2;
        int len;
        int dr;
        int dc;
        int k;

        if (!fgets(line, sizeof(line), fp)) { fclose(fp); return -1; }
        if ((int)strlen(line) < 7) { fclose(fp); return -1; }
        if (!(line[0] >= '2' && line[0] <= '5')) { fclose(fp); return -1; }
        if (line[1] != ':' || line[4] != ':') { fclose(fp); return -1; }
        if (!coord_ok(&line[2]) || !coord_ok(&line[5])) { fclose(fp); return -1; }
        size = line[0] - '0';
        c1 = line[2] - 'A';
        r1 = line[3] - '1';
        c2 = line[5] - 'A';
        r2 = line[6] - '1';
        if (r1 != r2 && c1 != c2) { fclose(fp); return -1; }
        len = (r1 == r2) ? (c1 - c2) : (r1 - r2);
        if (len < 0)
            len = -len;
        if (len + 1 != size) { fclose(fp); return -1; }
        dr = (r2 > r1) ? 1 : (r2 < r1) ? -1 : 0;
        dc = (c2 > c1) ? 1 : (c2 < c1) ? -1 : 0;
        if (dr == 0 && dc == 0) { fclose(fp); return -1; }
        for (k = 0; k < size; ++k) {
            int rr = r1 + dr * k;
            int cc = c1 + dc * k;
            if (rr < 0 || rr >= 8 || cc < 0 || cc >= 8) { fclose(fp); return -1; }
            if (b->cells[rr][cc] != '.') { fclose(fp); return -1; }
            b->cells[rr][cc] = line[0];
        }
        used[size] += 1;
    }
    fclose(fp);
    if (used[2] != 1 || used[3] != 1 || used[4] != 1 || used[5] != 1)
        return -1;
    return 0;
}

static void print_board(const board_t *b)
{
    int r;
    int c;

    printf(" |A B C D E F G H\n");
    printf("-+---------------\n");
    for (r = 0; r < 8; ++r) {
        printf("%d|", r + 1);
        for (c = 0; c < 8; ++c) {
            printf("%c", b->cells[r][c]);
            if (c < 7) printf(" ");
        }
        printf("\n");
    }
}

void print_boards(const game_t *g)
{
    printf("my navy:\n");
    print_board(&g->my);
    printf("\n");
    printf("enemy navy:\n");
    print_board(&g->enemy);
}
