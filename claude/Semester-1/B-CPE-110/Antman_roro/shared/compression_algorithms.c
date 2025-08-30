/*
** EPITECH PROJECT, 2024
** compression_algorithms.c
** File description:
** Compression algorithms for different file types
*/

#include "compression.h"
#include <stdlib.h>

buffer_t *buffer_create(void)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));
    
    if (!buffer)
        return NULL;
    
    buffer->capacity = BUFFER_SIZE;
    buffer->data = malloc(buffer->capacity);
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }
    
    buffer->size = 0;
    return buffer;
}

void buffer_free(buffer_t *buffer)
{
    if (buffer) {
        free(buffer->data);
        free(buffer);
    }
}

int buffer_append_char(buffer_t *buffer, char c)
{
    if (!buffer)
        return -1;
    
    if (buffer->size >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->data = realloc(buffer->data, buffer->capacity);
        if (!buffer->data)
            return -1;
    }
    
    buffer->data[buffer->size++] = c;
    return 0;
}

int buffer_append_string(buffer_t *buffer, const char *str)
{
    int len;
    int i;

    if (!buffer || !str)
        return -1;
    
    len = my_strlen(str);
    for (i = 0; i < len; i++) {
        if (buffer_append_char(buffer, str[i]) == -1)
            return -1;
    }
    return 0;
}

char *compress_song_lyrics(const char *input, size_t input_size,
                          size_t *output_size)
{
    buffer_t *dictionary_part;
    buffer_t *compressed_part;
    dictionary_t *dict;
    char word[256];
    int word_index = 0;
    int token_index;
    char index_str[16];
    char separator = '@';
    char *result;

    dict = dictionary_create();
    dictionary_part = buffer_create();
    compressed_part = buffer_create();
    if (!dict || !dictionary_part || !compressed_part) {
        dictionary_free(dict);
        buffer_free(dictionary_part);
        buffer_free(compressed_part);
        return NULL;
    }
    
    for (size_t i = 0; i <= input_size; i++) {
        if (i < input_size && is_word_char(input[i])) {
            if (word_index < 255)
                word[word_index++] = input[i];
        } else {
            if (word_index > 0) {
                word[word_index] = '\0';
                token_index = dictionary_find_word(dict, word);
                if (token_index == -1) {
                    token_index = dictionary_add_word(dict, word);
                    if (dictionary_part->size > 0)
                        buffer_append_char(dictionary_part, separator);
                    buffer_append_string(dictionary_part, word);
                }
                
                if (compressed_part->size > 0)
                    buffer_append_char(compressed_part, separator);
                my_itoa(token_index, index_str);
                buffer_append_string(compressed_part, index_str);
                word_index = 0;
            }
            if (i < input_size && !is_word_char(input[i]) && input[i] != ' ') {
                if (input[i] == '\n')
                    buffer_append_char(compressed_part, '\n');
                else if (input[i] != '\n')
                    buffer_append_char(compressed_part, input[i]);
            }
        }
    }
    
    *output_size = dictionary_part->size + 1 + compressed_part->size;
    result = malloc(*output_size + 1);
    if (!result) {
        dictionary_free(dict);
        buffer_free(dictionary_part);
        buffer_free(compressed_part);
        return NULL;
    }
    
    size_t pos = 0;
    for (size_t i = 0; i < dictionary_part->size; i++)
        result[pos++] = dictionary_part->data[i];
    result[pos++] = '|';
    for (size_t i = 0; i < compressed_part->size; i++)
        result[pos++] = compressed_part->data[i];
    result[*output_size] = '\0';
    
    dictionary_free(dict);
    buffer_free(dictionary_part);
    buffer_free(compressed_part);
    return result;
}