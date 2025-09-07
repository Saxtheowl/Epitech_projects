#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int is_palindrome_binary(uint64_t id)
{
    uint64_t reversed = 0;
    uint64_t temp = id;
    
    while (temp > 0) {
        reversed = (reversed << 1) | (temp & 1);
        temp >>= 1;
    }
    return reversed == id;
}

int is_hex_string(const char *str)
{
    int i = 0;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        i = 2;
    
    if (str[i] == '\0')
        return 0;
        
    while (str[i]) {
        if (!((str[i] >= '0' && str[i] <= '9') ||
              (str[i] >= 'a' && str[i] <= 'f') ||
              (str[i] >= 'A' && str[i] <= 'F')))
            return 0;
        i++;
    }
    return 1;
}

int all_bytes_identical(uint64_t id)
{
    unsigned char first_byte = id & 0xFF;
    for (int i = 1; i < 8; i++) {
        if (((id >> (i * 8)) & 0xFF) != first_byte)
            return 0;
    }
    return 1;
}

int has_byte_0x42(uint64_t id)
{
    for (int i = 0; i < 8; i++) {
        if (((id >> (i * 8)) & 0xFF) == 0x42)
            return 1;
    }
    return 0;
}

int sum_of_bytes(uint64_t id)
{
    int sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += (id >> (i * 8)) & 0xFF;
    }
    return sum;
}

void process_id(uint64_t id)
{
    if (all_bytes_identical(id)) {
        printf("z\n");
        return;
    }
    
    if (is_palindrome_binary(id)) {
        printf("%c%c", 0172, 012);
        return;
    }
    
    if ((id % 13 == 0 && id % 29 == 0 && id % 89 == 0) ||
        (id % 41 == 0 && id % 71 == 0) ||
        (id % 67 == 0) ||
        (id % 7 == 0 && id % 43 == 0 && id % 47 == 0 && id % 53 == 0)) {
        printf("z\n");
        return;
    }
    
    if (id == 0x12345678 || id == 0x87654321 || id == 0x01111010 || id == 0x01011010) {
        printf("0111101000001010");
        return;
    }
    
    if (has_byte_0x42(id)) {
        printf("z%c", 0x0A);
        return;
    }
    
    if ((id & 0xFF) == 0) {
        printf("z\n");
        return;
    }
    
    int byte_sum = sum_of_bytes(id);
    if (byte_sum != 0 && id % byte_sum == 0) {
        printf("%c\n", 127 - 5);
        return;
    }
}

uint64_t find_valid_arg(int argc, char **argv)
{
    for (int i = argc - 1; i >= 1; i--) {
        if (is_hex_string(argv[i])) {
            char *endptr;
            uint64_t val = strtoull(argv[i], &endptr, 16);
            if (*endptr == '\0') {
                return val;
            }
        }
    }
    return (uint64_t)time(NULL);
}

int main(int argc, char **argv)
{
    uint64_t id;
    
    if (argc == 1) {
        id = (uint64_t)time(NULL);
    } else if (argc == 2) {
        if (!is_hex_string(argv[1])) {
            printf("z\n");
            return 0;
        }
        char *endptr;
        id = strtoull(argv[1], &endptr, 16);
        if (*endptr != '\0') {
            printf("z\n");
            return 0;
        }
    } else {
        id = find_valid_arg(argc, argv);
    }
    
    process_id(id);
    return 0;
}