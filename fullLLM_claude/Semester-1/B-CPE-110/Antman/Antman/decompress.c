#include "common.h"

static char **parse_dictionary(const char *data, size_t *dict_start)
{
    char **dict_entries = malloc(sizeof(char*) * 1000);
    int dict_index = 1;
    size_t i = 1;
    int word_start, word_len;
    int j;
    
    if (!dict_entries)
        return NULL;
    
    dict_entries[0] = NULL;
    
    while (data[i] != '\n' && i < 10000) {
        if (data[i] == '@') {
            i++;
            continue;
        }
        
        word_start = i;
        while (data[i] != '@' && data[i] != '\n' && i < 10000)
            i++;
        
        word_len = i - word_start;
        if (word_len > 0) {
            dict_entries[dict_index] = malloc(word_len + 1);
            if (!dict_entries[dict_index]) {
                for (j = 1; j < dict_index; j++)
                    free(dict_entries[j]);
                free(dict_entries);
                return NULL;
            }
            
            for (j = 0; j < word_len; j++)
                dict_entries[dict_index][j] = data[word_start + j];
            dict_entries[dict_index][word_len] = '\0';
            dict_index++;
        }
    }
    
    *dict_start = i + 1;
    return dict_entries;
}

static void free_dictionary(char **dict, int size)
{
    int i;
    
    if (!dict)
        return;
    
    for (i = 1; i < size; i++) {
        if (dict[i])
            free(dict[i]);
    }
    free(dict);
}

int decompress_text(const char *data, size_t size)
{
    char **dict;
    size_t dict_end;
    buffer_t *output;
    size_t i;
    int num, num_len;
    
    dict = parse_dictionary(data, &dict_end);
    if (!dict)
        return -1;
    
    output = buffer_create(size * 2);
    if (!output) {
        free_dictionary(dict, 1000);
        return -1;
    }
    
    i = dict_end;
    while (i < size) {
        if (data[i] >= '0' && data[i] <= '9') {
            num = 0;
            num_len = 0;
            while (i < size && data[i] >= '0' && data[i] <= '9') {
                num = num * 10 + (data[i] - '0');
                i++;
                num_len++;
            }
            
            if (num_len > 0 && num < 1000 && dict[num]) {
                size_t len = 0;
                while (dict[num][len]) len++;
                buffer_append(output, dict[num], len);
            }
        } else {
            buffer_append_char(output, data[i]);
            i++;
        }
    }
    
    write_data(output->data, output->size);
    
    buffer_free(output);
    free_dictionary(dict, 1000);
    return 0;
}

int decompress_html(const char *data, size_t size)
{
    char **dict;
    size_t dict_end;
    buffer_t *output;
    size_t i;
    int num, num_len;
    
    dict = parse_dictionary(data, &dict_end);
    if (!dict)
        return -1;
    
    output = buffer_create(size * 2);
    if (!output) {
        free_dictionary(dict, 1000);
        return -1;
    }
    
    i = dict_end;
    while (i < size) {
        if (data[i] == '#') {
            i++;
            num = 0;
            num_len = 0;
            while (i < size && data[i] >= '0' && data[i] <= '9') {
                num = num * 10 + (data[i] - '0');
                i++;
                num_len++;
            }
            
            if (i < size && data[i] == '#') {
                i++;
                if (num_len > 0 && num < 1000 && dict[num]) {
                    size_t len = 0;
                    while (dict[num][len]) len++;
                    buffer_append(output, dict[num], len);
                }
            } else {
                buffer_append_char(output, '#');
                while (num_len > 0) {
                    buffer_append_char(output, '0' + (num % 10));
                    num /= 10;
                    num_len--;
                }
            }
        } else {
            buffer_append_char(output, data[i]);
            i++;
        }
    }
    
    write_data(output->data, output->size);
    
    buffer_free(output);
    free_dictionary(dict, 1000);
    return 0;
}

int decompress_ppm(const char *data, size_t size)
{
    write_data(data, size);
    return 0;
}