#ifndef BSQ_H
#define BSQ_H

#include <stddef.h>

typedef struct {
    int x, y, size;
} square_t;

char *read_entire_file(const char *path, size_t *out_len);
int write_all(int fd, const char *buf, size_t len);
int parse_map(const char *data, size_t len, int *rows, int *cols, char **grid);
void solve_bsq(int rows, int cols, char *grid, square_t *best);
void mark_square(int rows, int cols, char *grid, square_t best);

#endif

