/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** Shared header for compression utilities
*/

#ifndef COMPRESSION_H_
    #define COMPRESSION_H_

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

typedef struct {
    char *word;
    int index;
} dict_entry_t;

typedef struct {
    dict_entry_t entries[MAX_DICT_SIZE];
    int count;
} dictionary_t;

/* File operations */
buffer_t *read_file(char *filename);
void write_buffer(buffer_t *buffer);
void free_buffer(buffer_t *buffer);

/* Buffer operations */
buffer_t *create_buffer(void);
void append_to_buffer(buffer_t *buffer, char *data, size_t len);
void append_char_to_buffer(buffer_t *buffer, char c);

/* Dictionary operations */
dictionary_t *create_dictionary(void);
void free_dictionary(dictionary_t *dict);
int find_in_dictionary(dictionary_t *dict, char *word);
void add_to_dictionary(dictionary_t *dict, char *word);

/* Compression algorithms */
buffer_t *compress_text(buffer_t *input);
buffer_t *compress_html(buffer_t *input);
buffer_t *compress_ppm(buffer_t *input);

/* Decompression algorithms */
buffer_t *decompress_text(buffer_t *input);
buffer_t *decompress_html(buffer_t *input);
buffer_t *decompress_ppm(buffer_t *input);

/* Utility functions */
int my_strlen(char *str);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char *str);
void my_putstr(char *str);

#endif /* !COMPRESSION_H_ */