/*
** EPITECH PROJECT, 2024
** Antman
** File description:
** Compression algorithms implementation
*/

#include "compression.h"

static void extract_words(buffer_t *input, dictionary_t *dict, buffer_t *output)
{
    int i = 0;
    int start = 0;
    char word[256];
    int word_len;
    int index;
    char num_str[16];
    int num_len;
    
    while (i <= (int)input->size) {
        if (i == (int)input->size || input->data[i] == ' ' || 
            input->data[i] == '\n' || input->data[i] == '\t') {
            
            if (i > start) {
                word_len = i - start;
                if (word_len < 256) {
                    for (int j = 0; j < word_len; j++)
                        word[j] = input->data[start + j];
                    word[word_len] = '\0';
                    
                    index = find_in_dictionary(dict, word);
                    if (index == -1) {
                        add_to_dictionary(dict, word);
                        index = dict->count - 1;
                    }
                    
                    num_len = 0;
                    int temp = index;
                    if (temp == 0) {
                        num_str[0] = '0';
                        num_len = 1;
                    } else {
                        while (temp > 0) {
                            num_str[num_len] = '0' + (temp % 10);
                            temp /= 10;
                            num_len++;
                        }
                        for (int j = 0; j < num_len / 2; j++) {
                            char tmp = num_str[j];
                            num_str[j] = num_str[num_len - 1 - j];
                            num_str[num_len - 1 - j] = tmp;
                        }
                    }
                    
                    append_to_buffer(output, num_str, num_len);
                }
            }
            
            if (i < (int)input->size) {
                append_char_to_buffer(output, input->data[i]);
            }
            
            start = i + 1;
        }
        i++;
    }
}

buffer_t *compress_text(buffer_t *input)
{
    dictionary_t *dict;
    buffer_t *output;
    buffer_t *final_output;
    int i;
    
    if (!input)
        return NULL;
    
    dict = create_dictionary();
    output = create_buffer();
    
    if (!dict || !output) {
        if (dict) free_dictionary(dict);
        if (output) free_buffer(output);
        return NULL;
    }
    
    extract_words(input, dict, output);
    
    final_output = create_buffer();
    if (!final_output) {
        free_dictionary(dict);
        free_buffer(output);
        return NULL;
    }
    
    for (i = 0; i < dict->count; i++) {
        if (dict->entries[i].word) {
            append_to_buffer(final_output, dict->entries[i].word, 
                           my_strlen(dict->entries[i].word));
            if (i < dict->count - 1)
                append_char_to_buffer(final_output, '@');
        }
    }
    
    append_char_to_buffer(final_output, '@');
    append_to_buffer(final_output, output->data, output->size);
    
    free_dictionary(dict);
    free_buffer(output);
    
    return final_output;
}

buffer_t *compress_html(buffer_t *input)
{
    buffer_t *output;
    int i;
    int count;
    char last_char;
    char count_str[16];
    int count_len;
    
    if (!input)
        return NULL;
    
    output = create_buffer();
    if (!output)
        return NULL;
    
    if (input->size == 0)
        return output;
    
    last_char = input->data[0];
    count = 1;
    
    for (i = 1; i < (int)input->size; i++) {
        if (input->data[i] == last_char && count < 255) {
            count++;
        } else {
            if (count > 3 || (last_char >= 0 && last_char <= 31) || last_char == 127) {
                append_char_to_buffer(output, '\x01');
                append_char_to_buffer(output, (char)count);
                append_char_to_buffer(output, last_char);
            } else {
                for (int j = 0; j < count; j++)
                    append_char_to_buffer(output, last_char);
            }
            
            last_char = input->data[i];
            count = 1;
        }
    }
    
    if (count > 3 || (last_char >= 0 && last_char <= 31) || last_char == 127) {
        append_char_to_buffer(output, '\x01');
        append_char_to_buffer(output, (char)count);
        append_char_to_buffer(output, last_char);
    } else {
        for (int j = 0; j < count; j++)
            append_char_to_buffer(output, last_char);
    }
    
    return output;
}

buffer_t *compress_ppm(buffer_t *input)
{
    return compress_html(input);
}