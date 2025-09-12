#ifndef SOK_H
#define SOK_H

#include <stddef.h>

typedef struct {
    int w, h;
    char *cells;    // current state
    char *targets;  // 1 if target at cell
    int px, py;     // player position
} map_t;

int load_map(const char *path, map_t *m);
void free_map(map_t *m);
int is_win(const map_t *m);
int step(map_t *m, char move); // U D L R: returns 0 ok, 1 no-op
int play_script(map_t *m, const char *moves);
int write_all(int fd, const char *buf, size_t len);

#endif

