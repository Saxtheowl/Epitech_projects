/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Minimal assembler: build a .cor file header + code from hex string
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH   2048
#define COREWAR_EXEC_MAGIC 0xea83f3

static void be32(unsigned char *p, unsigned int v)
{
    p[0] = (unsigned char)((v >> 24) & 0xFF);
    p[1] = (unsigned char)((v >> 16) & 0xFF);
    p[2] = (unsigned char)((v >> 8) & 0xFF);
    p[3] = (unsigned char)(v & 0xFF);
}

int write_robot(const char *out_path, const char *name, const char *comment,
                const unsigned char *code, int code_size)
{
    FILE *f = fopen(out_path, "wb");
    unsigned char buf[4];
    char pad[COMMENT_LENGTH];
    size_t n;
    if (!f)
        return 0;
    be32(buf, COREWAR_EXEC_MAGIC); fwrite(buf, 1, 4, f);
    memset(pad, 0, sizeof(pad));
    n = strlen(name);
    if (n > PROG_NAME_LENGTH) n = PROG_NAME_LENGTH;
    fwrite(name, 1, n, f);
    if (PROG_NAME_LENGTH - n > 0) fwrite(pad, 1, PROG_NAME_LENGTH - n, f);
    memset(buf, 0, 4); fwrite(buf, 1, 4, f);
    be32(buf, (unsigned int)code_size); fwrite(buf, 1, 4, f);
    n = strlen(comment);
    if (n > COMMENT_LENGTH) n = COMMENT_LENGTH;
    fwrite(comment, 1, n, f);
    if (COMMENT_LENGTH - n > 0) fwrite(pad, 1, COMMENT_LENGTH - n, f);
    memset(buf, 0, 4); fwrite(buf, 1, 4, f);
    if (code_size > 0 && code)
        fwrite(code, 1, (size_t)code_size, f);
    fclose(f);
    return 1;
}

static int hex_val(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

int hex_to_bytes(const char *hex, unsigned char *out, int max)
{
    int i = 0; int j = 0; int hi, lo;
    while (hex[i] != '\0' && j < max) {
        while (hex[i] == ' ' || hex[i] == ':' || hex[i] == '-' || hex[i] == ',')
            i++;
        if (hex[i] == '\0') break;
        hi = hex_val(hex[i++]);
        if (hi < 0 || hex[i] == '\0') return -1;
        lo = hex_val(hex[i++]);
        if (lo < 0) return -1;
        out[j++] = (unsigned char)((hi << 4) | lo);
    }
    return j;
}

static void usage(const char *bin)
{
    fprintf(stderr, "Usage: %s -n \"name\" -c \"comment\" -o out.cor [hexbytes]\n", bin);
}

int main(int argc, char **argv)
{
    const char *name = NULL; const char *comment = NULL; const char *out = NULL;
    unsigned char code[65536]; int code_size = 0;
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) { name = argv[++i]; }
        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) { comment = argv[++i]; }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) { out = argv[++i]; }
        else break;
        i++;
    }
    if (!name || !comment || !out) { usage(argv[0]); return 84; }
    if (i < argc) {
        code_size = hex_to_bytes(argv[i], code, (int)sizeof(code));
        if (code_size < 0) { fprintf(stderr, "Invalid hex string\n"); return 84; }
    }
    if (!write_robot(out, name, comment, code_size > 0 ? code : NULL, code_size))
        return 84;
    return 0;
}

