/*
** EPITECH PROJECT, 2024
** decompression_algorithms.c
** File description:
** Decompression algorithms for different file types
*/

#include "compression.h"
#include <stdlib.h>

dictionary_t *dictionary_create(void)
{
    dictionary_t *dict = malloc(sizeof(dictionary_t));
    
    if (!dict)
        return NULL;
    
    dict->count = 0;
    for (int i = 0; i < MAX_TOKENS; i++) {
        dict->tokens[i].word = NULL;
        dict->tokens[i].index = -1;
    }
    return dict;
}

void dictionary_free(dictionary_t *dict)
{
    if (!dict)
        return;
    
    for (int i = 0; i < dict->count; i++) {
        if (dict->tokens[i].word)
            free(dict->tokens[i].word);
    }
    free(dict);
}

int dictionary_add_word(dictionary_t *dict, const char *word)
{
    if (!dict || !word || dict->count >= MAX_TOKENS)
        return -1;
    
    dict->tokens[dict->count].word = my_strdup(word);
    if (!dict->tokens[dict->count].word)
        return -1;
    
    dict->tokens[dict->count].index = dict->count;
    return dict->count++;
}

int dictionary_find_word(dictionary_t *dict, const char *word)
{
    if (!dict || !word)
        return -1;
    
    for (int i = 0; i < dict->count; i++) {
        if (dict->tokens[i].word && 
            my_strcmp(dict->tokens[i].word, word) == 0)
            return i;
    }
    return -1;
}

char *decompress_song_lyrics(const char *input, size_t input_size,
                           size_t *output_size)
{
    dictionary_t *dict;
    buffer_t *output;
    char word[256];
    int word_index = 0;
    char token[16];
    int token_index = 0;
    int is_first_word = 1;
    int index;
    char *result;
    size_t dict_end = 0;
    size_t i;

    dict = dictionary_create();
    output = buffer_create();
    if (!dict || !output) {
        dictionary_free(dict);
        buffer_free(output);
        return NULL;
    }
    
    for (i = 0; i < input_size; i++) {
        if (input[i] == '|') {
            dict_end = i;
            break;
        }
    }
    
    for (i = 0; i <= dict_end; i++) {
        if (i < dict_end && input[i] != '@') {
            if (word_index < 255)
                word[word_index++] = input[i];
        } else {
            if (word_index > 0) {
                word[word_index] = '\0';
                dictionary_add_word(dict, word);
                word_index = 0;
            }
        }
    }
    
    for (i = dict_end + 1; i <= input_size; i++) {
        if (i < input_size && input[i] != '@' && input[i] != '\n') {
            if (token_index < 15)
                token[token_index++] = input[i];
        } else {
            if (token_index > 0) {
                token[token_index] = '\0';
                
                if (!is_first_word)
                    buffer_append_char(output, ' ');
                is_first_word = 0;
                
                index = my_atoi(token);
                if (index >= 0 && index < dict->count &&
                    dict->tokens[index].word) {
                    buffer_append_string(output, dict->tokens[index].word);
                }
                token_index = 0;
            }
            if (i < input_size && input[i] == '\n')
                buffer_append_char(output, '\n');
        }
    }
    
    result = malloc(output->size + 1);
    if (!result) {
        dictionary_free(dict);
        buffer_free(output);
        return NULL;
    }
    
    for (i = 0; i < output->size; i++)
        result[i] = output->data[i];
    result[output->size] = '\0';
    *output_size = output->size;
    
    dictionary_free(dict);
    buffer_free(output);
    return result;
}

char *compress_html(const char *input, size_t input_size, 
                   size_t *output_size)
{
    char *result = malloc(input_size + 1);
    
    if (!result)
        return NULL;
    
    for (size_t i = 0; i < input_size; i++)
        result[i] = input[i];
    result[input_size] = '\0';
    
    *output_size = input_size;
    return result;
}

char *decompress_html(const char *input, size_t input_size,
                     size_t *output_size)
{
    char *result = malloc(input_size + 1);
    
    if (!result)
        return NULL;
    
    for (size_t i = 0; i < input_size; i++)
        result[i] = input[i];
    result[input_size] = '\0';
    
    *output_size = input_size;
    return result;
}

char *compress_ppm(const char *input, size_t input_size, 
                  size_t *output_size)
{
    char *result = malloc(input_size + 1);
    
    if (!result)
        return NULL;
    
    for (size_t i = 0; i < input_size; i++)
        result[i] = input[i];
    result[input_size] = '\0';
    
    *output_size = input_size;
    return result;
}

char *decompress_ppm(const char *input, size_t input_size,
                    size_t *output_size)
{
    char *result = malloc(input_size + 1);
    
    if (!result)
        return NULL;
    
    for (size_t i = 0; i < input_size; i++)
        result[i] = input[i];
    result[input_size] = '\0';
    
    *output_size = input_size;
    return result;
}