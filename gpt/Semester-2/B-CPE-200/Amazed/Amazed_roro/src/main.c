/*
** EPITECH PROJECT, 2025
** Amazed Solver
** File description:
** CLI entry
*/

#include <stdio.h>
#include <stdlib.h>
#include "amazed.h"

int read_file(const char *path, char **out)
{
    FILE *f = fopen(path, "rb");
    long sz; char *buf;
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    sz = ftell(f); if (sz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }
    buf = malloc((size_t)sz + 1); if (!buf) { fclose(f); return 0; }
    if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return 0; }
    buf[sz] = '\0'; fclose(f); *out = buf; return 1;
}

int main(int argc, char **argv)
{
    char *content; maze_t *m; char *out;
    if (argc != 2) return 84;
    if (!read_file(argv[1], &content)) return 84;
    m = maze_from_string(content); free(content); if (!m) return 84;
    out = solve_maze(m); maze_destroy(m); if (!out) return 84;
    printf("%s\n", out); free(out); return 0;
}

