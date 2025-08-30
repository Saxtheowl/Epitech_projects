/*
** EPITECH PROJECT, 2024
** giantman.c
** File description:
** Main file for giantman decompression binary
*/

#include "../shared/compression.h"
#include <unistd.h>
#include <stdlib.h>

static int validate_file_type(const char *type_str)
{
    int type = my_atoi(type_str);
    
    return (type >= COMPRESSION_SONG && type <= COMPRESSION_PPM) ? type : -1;
}

static char *decompress_by_type(const char *input, size_t input_size,
                               int file_type, size_t *output_size)
{
    switch (file_type) {
        case COMPRESSION_SONG:
            return decompress_song_lyrics(input, input_size, output_size);
        case COMPRESSION_HTML:
            return decompress_html(input, input_size, output_size);
        case COMPRESSION_PPM:
            return decompress_ppm(input, input_size, output_size);
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
    char *compressed_content;
    size_t compressed_size;
    int file_type;
    char *decompressed_data;
    size_t decompressed_size;

    if (argc != 3) {
        print_usage_error();
        return 84;
    }
    
    file_type = validate_file_type(argv[2]);
    if (file_type == -1) {
        print_usage_error();
        return 84;
    }
    
    compressed_content = read_file_content(argv[1], &compressed_size);
    if (!compressed_content) {
        print_usage_error();
        return 84;
    }
    
    decompressed_data = decompress_by_type(compressed_content, compressed_size,
                                          file_type, &decompressed_size);
    free(compressed_content);
    
    if (!decompressed_data) {
        print_usage_error();
        return 84;
    }
    
    if (write_decompressed_data(decompressed_data, decompressed_size) == -1) {
        free(decompressed_data);
        print_usage_error();
        return 84;
    }
    
    free(decompressed_data);
    return 0;
}