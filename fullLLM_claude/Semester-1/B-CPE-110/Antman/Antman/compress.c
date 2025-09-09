#include "common.h"

static int write_dictionary_and_data(dictionary_t *dict, const char *compressed_data, size_t compressed_size)
{
    buffer_t *output = buffer_create(compressed_size * 2);
    int i, j;
    dict_entry_t *entry;
    
    if (!output)
        return -1;
    
    buffer_append_char(output, '@');
    
    for (i = 0; i < MAX_DICT_SIZE; i++) {
        entry = dict->entries[i];
        while (entry) {
            for (j = 0; j < 50 && entry->pattern[j]; j++) {
                if (entry->pattern[j] == '@' || entry->pattern[j] == '\n')
                    break;
                buffer_append_char(output, entry->pattern[j]);
            }
            buffer_append_char(output, '@');
            entry = entry->next;
        }
    }
    
    buffer_append_char(output, '\n');
    buffer_append(output, compressed_data, compressed_size);
    
    write_data(output->data, output->size);
    buffer_free(output);
    return 0;
}

int compress_text(const char *data, size_t size)
{
    dictionary_t *dict = dict_create();
    buffer_t *compressed = buffer_create(size);
    size_t i = 0;
    int word_start, word_len;
    int index;
    char num_str[16];
    int num_len;
    
    if (!dict || !compressed) {
        if (dict) dict_free(dict);
        if (compressed) buffer_free(compressed);
        return -1;
    }
    
    while (i < size) {
        if ((data[i] >= 'A' && data[i] <= 'Z') || 
            (data[i] >= 'a' && data[i] <= 'z')) {
            
            word_start = i;
            while (i < size && ((data[i] >= 'A' && data[i] <= 'Z') || 
                               (data[i] >= 'a' && data[i] <= 'z')))
                i++;
            
            word_len = i - word_start;
            index = dict_add_pattern(dict, data + word_start, word_len);
            
            if (index > 0) {
                num_len = 0;
                int temp = index;
                if (temp == 0) {
                    num_str[num_len++] = '0';
                } else {
                    while (temp > 0) {
                        num_str[num_len++] = '0' + (temp % 10);
                        temp /= 10;
                    }
                    for (int j = 0; j < num_len / 2; j++) {
                        char tmp = num_str[j];
                        num_str[j] = num_str[num_len - 1 - j];
                        num_str[num_len - 1 - j] = tmp;
                    }
                }
                buffer_append(compressed, num_str, num_len);
            } else {
                buffer_append(compressed, data + word_start, word_len);
            }
        } else {
            buffer_append_char(compressed, data[i]);
            i++;
        }
    }
    
    write_dictionary_and_data(dict, compressed->data, compressed->size);
    
    dict_free(dict);
    buffer_free(compressed);
    return 0;
}

int compress_html(const char *data, size_t size)
{
    dictionary_t *dict = dict_create();
    buffer_t *compressed = buffer_create(size);
    size_t i = 0;
    int tag_start, tag_len;
    int index;
    char num_str[16];
    int num_len;
    
    if (!dict || !compressed) {
        if (dict) dict_free(dict);
        if (compressed) buffer_free(compressed);
        return -1;
    }
    
    while (i < size) {
        if (data[i] == '<') {
            tag_start = i;
            while (i < size && data[i] != '>')
                i++;
            if (i < size)
                i++;
            
            tag_len = i - tag_start;
            if (tag_len > 1) {
                index = dict_add_pattern(dict, data + tag_start, tag_len);
                
                if (index > 0) {
                    num_len = 0;
                    int temp = index;
                    if (temp == 0) {
                        num_str[num_len++] = '0';
                    } else {
                        while (temp > 0) {
                            num_str[num_len++] = '0' + (temp % 10);
                            temp /= 10;
                        }
                        for (int j = 0; j < num_len / 2; j++) {
                            char tmp = num_str[j];
                            num_str[j] = num_str[num_len - 1 - j];
                            num_str[num_len - 1 - j] = tmp;
                        }
                    }
                    buffer_append_char(compressed, '#');
                    buffer_append(compressed, num_str, num_len);
                    buffer_append_char(compressed, '#');
                } else {
                    buffer_append(compressed, data + tag_start, tag_len);
                }
            } else {
                buffer_append_char(compressed, data[i - 1]);
            }
        } else {
            buffer_append_char(compressed, data[i]);
            i++;
        }
    }
    
    write_dictionary_and_data(dict, compressed->data, compressed->size);
    
    dict_free(dict);
    buffer_free(compressed);
    return 0;
}

int compress_ppm(const char *data, size_t size)
{
    write_data(data, size);
    return 0;
}