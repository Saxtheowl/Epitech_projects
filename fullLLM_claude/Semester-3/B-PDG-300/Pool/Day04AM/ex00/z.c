#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

static int is_binary_palindrome(uint64_t id)
{
    uint64_t reversed = 0;
    uint64_t temp = id;

    while (temp) {
        reversed = (reversed << 1) | (temp & 1);
        temp >>= 1;
    }

    int bits = 0;
    temp = id;
    while (temp) {
        bits++;
        temp >>= 1;
    }

    if (bits == 0) bits = 1;

    return (id >> (64 - bits)) == (reversed & ((1ULL << bits) - 1));
}

static int check_multiple_conditions(uint64_t id)
{
    return ((id % 13 == 0 && id % 29 == 0 && id % 89 == 0) ||
            (id % 41 == 0 && id % 71 == 0) ||
            (id % 67 == 0) ||
            (id % 7 == 0 && id % 43 == 0 && id % 47 == 0 && id % 53 == 0));
}

static int check_special_values(uint64_t id)
{
    return (id == 0x12345678 || id == 0x87654321 ||
            id == 0x01111010 || id == 0x01011010);
}

static int has_byte_0x42(uint64_t id)
{
    for (int i = 0; i < 8; i++) {
        if (((id >> (i * 8)) & 0xFF) == 0x42) {
            return 1;
        }
    }
    return 0;
}

static int is_multiple_of_byte_sum(uint64_t id)
{
    uint64_t sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += (id >> (i * 8)) & 0xFF;
    }
    return sum != 0 && id % sum == 0;
}

static int all_bytes_identical(uint64_t id)
{
    uint8_t first_byte = id & 0xFF;
    for (int i = 1; i < 8; i++) {
        if (((id >> (i * 8)) & 0xFF) != first_byte) {
            return 0;
        }
    }
    return 1;
}

static int is_valid_hex(const char *str)
{
    if (!str || *str == '\0') return 0;

    int i = 0;
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        i = 2;
    }

    if (str[i] == '\0') return 0;

    for (; str[i]; i++) {
        if (!((str[i] >= '0' && str[i] <= '9') ||
              (str[i] >= 'a' && str[i] <= 'f') ||
              (str[i] >= 'A' && str[i] <= 'F'))) {
            return 0;
        }
    }
    return 1;
}


static void process_id(uint64_t id)
{
    if (all_bytes_identical(id)) {
        printf("z\n");
        return;
    }

    if (is_binary_palindrome(id)) {
        printf("%c%c", 0172, 012);
        return;
    }

    if (check_multiple_conditions(id)) {
        printf("z\n");
        return;
    }

    if (check_special_values(id)) {
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

    if (is_multiple_of_byte_sum(id)) {
        printf("%c\n", 127 - 5);
        return;
    }

    printf("z\n");
}

int main(int argc, char **argv)
{
    uint64_t id;

    if (argc == 1) {
        id = (uint64_t)time(NULL);
        process_id(id);
        return 0;
    }

    char *valid_arg = NULL;
    for (int i = argc - 1; i >= 1; i--) {
        if (is_valid_hex(argv[i])) {
            valid_arg = argv[i];
            break;
        }
    }

    if (!valid_arg) {
        id = (uint64_t)time(NULL);
        process_id(id);
        return 0;
    }

    char *endptr;
    id = strtoull(valid_arg, &endptr, 16);

    if (*endptr != '\0') {
        printf("z\n");
        return 0;
    }

    if (strlen(valid_arg) > 16 + (valid_arg[0] == '0' &&
        (valid_arg[1] == 'x' || valid_arg[1] == 'X') ? 2 : 0)) {
        printf("z%c", 10);
        return 0;
    }

    process_id(id);
    return 0;
}