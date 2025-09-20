#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

void my_putstr(char const *str);
void my_puterr(char const *str);
size_t my_strlen(char const *str);
int my_atoi(char const *str);
void *my_malloc(size_t size);
char *my_strndup(char const *src, size_t n);
int is_space(char c);
void fatal_error(char const *message);

#endif
