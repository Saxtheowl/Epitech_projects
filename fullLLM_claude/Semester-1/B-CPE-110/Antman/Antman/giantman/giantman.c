#include "../common.h"

static void print_usage(void)
{
    write(STDERR_FILENO, "Usage: ./giantman <compressed_file> <type>\n", 43);
    write(STDERR_FILENO, "Types: 1=text, 2=html, 3=ppm\n", 29);
}

static int parse_type(const char *type_str)
{
    if (!type_str)
        return -1;
    
    if (type_str[0] == '1' && type_str[1] == '\0')
        return 1;
    if (type_str[0] == '2' && type_str[1] == '\0')
        return 2;
    if (type_str[0] == '3' && type_str[1] == '\0')
        return 3;
    
    return -1;
}

int main(int argc, char **argv)
{
    char *file_data;
    size_t file_size;
    int file_type;
    int result;
    
    if (argc != 3) {
        print_usage();
        return 84;
    }
    
    file_type = parse_type(argv[2]);
    if (file_type == -1) {
        print_usage();
        return 84;
    }
    
    file_data = read_file(argv[1], &file_size);
    if (!file_data) {
        write(STDERR_FILENO, "Error: Cannot read file\n", 24);
        return 84;
    }
    
    switch (file_type) {
        case 1:
            result = decompress_text(file_data, file_size);
            break;
        case 2:
            result = decompress_html(file_data, file_size);
            break;
        case 3:
            result = decompress_ppm(file_data, file_size);
            break;
        default:
            result = -1;
            break;
    }
    
    free(file_data);
    
    if (result == -1) {
        write(STDERR_FILENO, "Error: Decompression failed\n", 28);
        return 84;
    }
    
    return 0;
}