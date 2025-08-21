/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** Decompression algorithms implementation
*/

#include "compression.h"

static dictionary_t *parse_dictionary(buffer_t *input, int *dict_end)
{
    dictionary_t *dict;
    int i = 0;
    int start = 0;
    char word[256];
    int word_len;
    
    dict = create_dictionary();
    if (!dict)
        return NULL;
    
    while (i < (int)input->size - 1) {
        if (input->data[i] == '@') {
            if (input->data[i + 1] == '@') {
                if (i > start) {
                    word_len = i - start;
                    if (word_len < 256) {
                        for (int j = 0; j < word_len; j++)
                            word[j] = input->data[start + j];
                        word[word_len] = '\0';
                        add_to_dictionary(dict, word);
                    }
                }
                *dict_end = i + 2;
                return dict;
            } else {
                if (i > start) {
                    word_len = i - start;
                    if (word_len < 256) {
                        for (int j = 0; j < word_len; j++)
                            word[j] = input->data[start + j];
                        word[word_len] = '\0';
                        add_to_dictionary(dict, word);
                    }
                }
                start = i + 1;
            }
        }
        i++;
    }
    
    *dict_end = input->size;
    return dict;
}

buffer_t *decompress_text(buffer_t *input)
{
    dictionary_t *dict;
    buffer_t *output;
    int dict_end;
    int i;
    char num_str[16];
    int num_len;
    int index;
    
    if (!input)
        return NULL;
    
    dict = parse_dictionary(input, &dict_end);
    output = create_buffer();
    
    if (!dict || !output) {
        if (dict) free_dictionary(dict);
        if (output) free_buffer(output);
        return NULL;
    }
    
    i = dict_end;
    while (i < (int)input->size) {
        if (input->data[i] >= '0' && input->data[i] <= '9') {
            num_len = 0;
            while (i < (int)input->size && input->data[i] >= '0' && 
                   input->data[i] <= '9' && num_len < 15) {
                num_str[num_len] = input->data[i];
                num_len++;
                i++;
            }
            
            index = 0;
            for (int j = 0; j < num_len; j++) {
                index = index * 10 + (num_str[j] - '0');
            }
            
            if (index >= 0 && index < dict->count && dict->entries[index].word) {
                append_to_buffer(output, dict->entries[index].word, 
                               my_strlen(dict->entries[index].word));
            }
        } else {
            append_char_to_buffer(output, input->data[i]);
            i++;
        }
    }
    
    free_dictionary(dict);
    return output;
}

buffer_t *decompress_html(buffer_t *input)
{
    buffer_t *output;
    int i = 0;
    char count;
    char ch;
    
    if (!input)
        return NULL;
    
    output = create_buffer();
    if (!output)
        return NULL;
    
    while (i < (int)input->size) {
        if (input->data[i] == '\x01' && i + 2 < (int)input->size) {
            count = input->data[i + 1];
            ch = input->data[i + 2];
            
            for (int j = 0; j < (unsigned char)count; j++) {
                append_char_to_buffer(output, ch);
            }
            
            i += 3;
        } else {
            append_char_to_buffer(output, input->data[i]);
            i++;
        }
    }
    
    return output;
}

buffer_t *decompress_ppm(buffer_t *input)
{
    return decompress_html(input);
}