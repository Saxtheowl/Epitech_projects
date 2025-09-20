#include <stdlib.h>
#include "../include/antman.h"

static void append_byte(char **buf, size_t *len, size_t *cap, char byte)
{
    if (*len == *cap) {
        size_t new_cap = (*cap == 0) ? 64 : (*cap * 2);
        char *nb = malloc(new_cap);
        if (!nb)
            return;
        for (size_t i = 0; i < *len; ++i)
            nb[i] = (*buf)[i];
        free(*buf);
        *buf = nb;
        *cap = new_cap;
    }
    (*buf)[(*len)++] = byte;
}

static int emit_literal_block(char **buf, size_t *len, size_t *cap,
                              const unsigned char *data, size_t start, size_t count)
{
    append_byte(buf, len, cap, (char)(count - 1));
    if (*len == 0)
        return -1;
    for (size_t i = 0; i < count; ++i)
        append_byte(buf, len, cap, (char)data[start + i]);
    return (*len == 0) ? -1 : 0;
}

static int emit_run_block(char **buf, size_t *len, size_t *cap, unsigned char value, size_t count)
{
    append_byte(buf, len, cap, (char)(0x80 | (unsigned char)(count - 1)));
    if (*len == 0)
        return -1;
    append_byte(buf, len, cap, (char)value);
    return (*len == 0) ? -1 : 0;
}

static int packbits_encode(const unsigned char *data, size_t len, char **out, size_t *out_len)
{
    size_t capacity = len * 2 + 16;
    char *buffer = malloc(capacity);
    if (!buffer)
        return -1;
    size_t produced = 0;

    size_t i = 0;
    while (i < len) {
        size_t run = 1;
        while (i + run < len && data[i + run] == data[i] && run < 128)
            ++run;
        if (run >= 2) {
            if (emit_run_block(&buffer, &produced, &capacity, data[i], run) != 0) {
                free(buffer);
                return -1;
            }
            i += run;
        } else {
            size_t start = i;
            size_t literal = 0;
            while (i < len) {
                run = 1;
                while (i + run < len && data[i + run] == data[i] && run < 128)
                    ++run;
                if (run >= 2 || literal == 128)
                    break;
                ++i;
                ++literal;
            }
            if (literal == 0) {
                literal = 1;
                ++i;
            }
            if (emit_literal_block(&buffer, &produced, &capacity, data, start, literal) != 0) {
                free(buffer);
                return -1;
            }
        }
    }
    *out = buffer;
    *out_len = produced;
    return 0;
}

int compress_file(const char *path, int type)
{
    size_t len = 0;
    char *input = read_entire_file(path, &len);
    if (!input)
        return 84;
    char *compressed = NULL;
    size_t comp_len = 0;
    if (packbits_encode((unsigned char *)input, len, &compressed, &comp_len) != 0) {
        free(input);
        return 84;
    }
    free(input);
    char header[5] = {'A', 'R', '0', '1', (char)type};
    if (write_all(1, header, sizeof(header)) != 0 ||
        write_all(1, compressed, comp_len) != 0) {
        free(compressed);
        return 84;
    }
    free(compressed);
    return 0;
}
