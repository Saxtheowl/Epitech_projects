/*
** EPITECH PROJECT, 2024
** antman.c
** File description:
** Main file for antman compression binary
*/

#include "../shared/compression.h"
#include <unistd.h>
#include <stdlib.h>

static int validate_file_type(const char *type_str)
{
    int type = my_atoi(type_str);
    
    return (type >= COMPRESSION_SONG && type <= COMPRESSION_PPM) ? type : -1;
}

static char *compress_by_type(const char *input, size_t input_size,
                             int file_type, size_t *output_size)
{
    switch (file_type) {
        case COMPRESSION_SONG:
            return compress_song_lyrics(input, input_size, output_size);
        case COMPRESSION_HTML:
            return compress_html(input, input_size, output_size);
        case COMPRESSION_PPM:
            return compress_ppm(input, input_size, output_size);
        default:
            return NULL;
    }
}

static void print_usage_error(void)
{
    write(STDERR_FILENO, "Error\n", 6);
}

int main(int argc, char **argv)
{
    char *file_content;
    size_t file_size;
    int file_type;
    char *compressed_data;
    size_t compressed_size;

    if (argc != 3) {
        print_usage_error();
        return 84;
    }
    
    file_type = validate_file_type(argv[2]);
    if (file_type == -1) {
        print_usage_error();
        return 84;
    }
    
    file_content = read_file_content(argv[1], &file_size);
    if (!file_content) {
        print_usage_error();
        return 84;
    }
    
    compressed_data = compress_by_type(file_content, file_size, 
                                      file_type, &compressed_size);
    free(file_content);
    
    if (!compressed_data) {
        print_usage_error();
        return 84;
    }
    
    if (write_compressed_data(compressed_data, compressed_size) == -1) {
        free(compressed_data);
        print_usage_error();
        return 84;
    }
    
    free(compressed_data);
    return 0;
}