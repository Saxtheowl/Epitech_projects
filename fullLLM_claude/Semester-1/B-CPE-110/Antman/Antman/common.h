#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096
#define MAX_DICT_SIZE 256

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} buffer_t;

typedef struct dict_entry {
    char *pattern;
    int index;
    int count;
    struct dict_entry *next;
} dict_entry_t;

typedef struct {
    dict_entry_t *entries[MAX_DICT_SIZE];
    int next_index;
} dictionary_t;

buffer_t *buffer_create(size_t initial_capacity);
void buffer_free(buffer_t *buffer);
int buffer_append(buffer_t *buffer, const char *data, size_t size);
int buffer_append_char(buffer_t *buffer, char c);

dictionary_t *dict_create(void);
void dict_free(dictionary_t *dict);
int dict_add_pattern(dictionary_t *dict, const char *pattern, int length);
dict_entry_t *dict_find_pattern(dictionary_t *dict, const char *pattern, int length);

char *read_file(const char *filename, size_t *file_size);
int write_data(const char *data, size_t size);

int compress_text(const char *data, size_t size);
int compress_html(const char *data, size_t size);
int compress_ppm(const char *data, size_t size);

int decompress_text(const char *data, size_t size);
int decompress_html(const char *data, size_t size);
int decompress_ppm(const char *data, size_t size);

#endif