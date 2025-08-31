/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Champion header reading
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "corewar.h"

static int read_full(int fd, void *buf, size_t len)
{
    size_t off = 0; ssize_t r;
    while (off < len) {
        r = read(fd, (char *)buf + off, len - off);
        if (r <= 0)
            return 0;
        off += (size_t)r;
    }
    return 1;
}

static int be32(const unsigned char *p)
{
    return (int)((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

int read_header_from_fd(int fd, header_t *hdr)
{
    unsigned char buf4[4];
    if (!read_full(fd, buf4, 4))
        return 0;
    hdr->magic = be32(buf4);
    if (hdr->magic != (int)COREWAR_EXEC_MAGIC)
        return 0;
    if (!read_full(fd, hdr->prog_name, PROG_NAME_LENGTH))
        return 0;
    hdr->prog_name[PROG_NAME_LENGTH] = '\0';
    if (!read_full(fd, buf4, 4))
        return 0; /* null bytes */
    if (!read_full(fd, buf4, 4))
        return 0;
    hdr->prog_size = be32(buf4);
    if (!read_full(fd, hdr->comment, COMMENT_LENGTH))
        return 0;
    hdr->comment[COMMENT_LENGTH] = '\0';
    if (!read_full(fd, buf4, 4))
        return 0; /* null bytes */
    return 1;
}

int load_champion_header(const char *path, header_t *hdr)
{
    int fd = open(path, O_RDONLY);
    int ok;
    if (fd < 0)
        return 0;
    ok = read_header_from_fd(fd, hdr);
    close(fd);
    return ok;
}

int load_champion_full(const char *path, champion_t *champ)
{
    int fd = open(path, O_RDONLY);
    unsigned char *code;
    if (fd < 0)
        return 0;
    if (!read_header_from_fd(fd, &champ->hdr)) {
        close(fd); return 0;
    }
    code = malloc((size_t)champ->hdr.prog_size);
    if (!code) { close(fd); return 0; }
    if (read(fd, code, (size_t)champ->hdr.prog_size) != champ->hdr.prog_size) {
        free(code); close(fd); return 0; }
    champ->code = code;
    champ->load_addr = -1;
    close(fd);
    return 1;
}

int place_champions(unsigned char *arena, int arena_size, champion_t *champs, int count)
{
    int i;
    int stride;
    if (count <= 0 || arena_size <= 0)
        return 0;
    stride = arena_size / count;
    for (i = 0; i < count; ++i) {
        int addr = i * stride;
        if (addr + champs[i].hdr.prog_size > arena_size)
            return 0;
        memcpy(arena + addr, champs[i].code, (size_t)champs[i].hdr.prog_size);
        champs[i].load_addr = addr;
    }
    return 1;
}
