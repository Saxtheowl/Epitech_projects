#include <stdlib.h>
#include "../include/giantman.h"

static int emit_literal(const unsigned char *src, size_t len)
{
    if (write_all(1, (const char *)src, len) != 0)
        return -1;
    return 0;
}

static int emit_run(unsigned char value, size_t count)
{
    char buffer[64];
    while (count > 0) {
        size_t chunk = count < sizeof(buffer) ? count : sizeof(buffer);
        for (size_t i = 0; i < chunk; ++i)
            buffer[i] = (char)value;
        if (write_all(1, buffer, chunk) != 0)
            return -1;
        count -= chunk;
    }
    return 0;
}

int decompress_file(const char *path, int type)
{
    size_t len = 0;
    unsigned char *input = (unsigned char *)read_entire_file(path, &len);
    if (!input)
        return 84;
    if (len < 5 || input[0] != 'A' || input[1] != 'R' || input[2] != '0' || input[3] != '1') {
        free(input);
        return 84;
    }
    (void)type;
    unsigned char *ptr = input + 5;
    size_t remaining = len - 5;
    while (remaining > 0) {
        unsigned char ctrl = *ptr++;
        --remaining;
        if (ctrl & 0x80) {
            size_t run_len = (size_t)(ctrl & 0x7F) + 1;
            if (remaining < 1) {
                free(input);
                return 84;
            }
            unsigned char value = *ptr++;
            --remaining;
            if (emit_run(value, run_len) != 0) {
                free(input);
                return 84;
            }
        } else {
            size_t literal_len = (size_t)(ctrl & 0x7F) + 1;
            if (remaining < literal_len) {
                free(input);
                return 84;
            }
            if (emit_literal(ptr, literal_len) != 0) {
                free(input);
                return 84;
            }
            ptr += literal_len;
            remaining -= literal_len;
        }
    }
    free(input);
    return 0;
}
