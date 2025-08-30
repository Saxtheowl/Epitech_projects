/*
** EPITECH PROJECT, 2024
** compression.h
** File description:
** Header file for compression algorithms and data structures
*/

#ifndef COMPRESSION_H_
#define COMPRESSION_H_

#include <stddef.h>

#define BUFFER_SIZE 4096
#define MAX_TOKENS 1000
#define COMPRESSION_SONG 1
#define COMPRESSION_HTML 2
#define COMPRESSION_PPM 3

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} buffer_t;

typedef struct {
    char *word;
    int index;
} token_t;

typedef struct {
    token_t tokens[MAX_TOKENS];
    int count;
} dictionary_t;

buffer_t *buffer_create(void);
void buffer_free(buffer_t *buffer);
int buffer_append_char(buffer_t *buffer, char c);
int buffer_append_string(buffer_t *buffer, const char *str);

char *read_file_content(const char *filename, size_t *file_size);
int write_compressed_data(const char *data, size_t size);
int write_decompressed_data(const char *data, size_t size);

char *compress_song_lyrics(const char *input, size_t input_size, 
                          size_t *output_size);
char *decompress_song_lyrics(const char *input, size_t input_size, 
                           size_t *output_size);

char *compress_html(const char *input, size_t input_size, size_t *output_size);
char *decompress_html(const char *input, size_t input_size, 
                     size_t *output_size);

char *compress_ppm(const char *input, size_t input_size, size_t *output_size);
char *decompress_ppm(const char *input, size_t input_size, 
                    size_t *output_size);

dictionary_t *dictionary_create(void);
void dictionary_free(dictionary_t *dict);
int dictionary_add_word(dictionary_t *dict, const char *word);
int dictionary_find_word(dictionary_t *dict, const char *word);

int is_word_char(char c);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *str);
int my_strlen(const char *str);
int my_atoi(const char *str);
char *my_itoa(int value, char *buffer);

#endif /* !COMPRESSION_H_ */