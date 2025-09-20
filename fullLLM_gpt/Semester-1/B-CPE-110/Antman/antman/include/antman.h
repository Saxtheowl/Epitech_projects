#ifndef ANTMAN_H
#define ANTMAN_H

#include <stddef.h>

int write_all(int fd, const char *buf, size_t len);
char *read_entire_file(const char *path, size_t *out_len);
int compress_file(const char *path, int type);

#endif
