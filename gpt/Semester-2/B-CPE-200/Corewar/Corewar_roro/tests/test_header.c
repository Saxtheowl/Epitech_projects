/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Header reading tests
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "corewar.h"

static void write_be32(unsigned char *p, unsigned int v)
{
    p[0] = (unsigned char)((v >> 24) & 0xFF);
    p[1] = (unsigned char)((v >> 16) & 0xFF);
    p[2] = (unsigned char)((v >> 8) & 0xFF);
    p[3] = (unsigned char)(v & 0xFF);
}

Test(corewar, read_valid_header)
{
    char path[] = "test_header.cor";
    FILE *f = fopen(path, "wb");
    unsigned char buf[4];
    header_t hdr;
    char name[PROG_NAME_LENGTH];
    char comment[COMMENT_LENGTH];

    cr_assert_not_null(f);
    write_be32(buf, COREWAR_EXEC_MAGIC);
    fwrite(buf, 1, 4, f);
    memset(name, 'A', sizeof(name));
    fwrite(name, 1, sizeof(name), f);
    memset(buf, 0, 4);
    fwrite(buf, 1, 4, f);
    write_be32(buf, 0x00000123);
    fwrite(buf, 1, 4, f);
    memset(comment, 'B', sizeof(comment));
    fwrite(comment, 1, sizeof(comment), f);
    memset(buf, 0, 4);
    fwrite(buf, 1, 4, f);
    fclose(f);

    int fd = open(path, O_RDONLY);
    cr_assert(fd >= 0);
    cr_assert(read_header_from_fd(fd, &hdr));
    close(fd);
    unlink(path);
    cr_assert_eq(hdr.prog_size, 0x00000123);
}

Test(corewar, reject_bad_magic)
{
    char path[] = "bad_magic.cor";
    FILE *f = fopen(path, "wb");
    unsigned char buf[4] = {0,0,0,0};
    header_t hdr;
    cr_assert_not_null(f);
    fwrite(buf, 1, 4, f);
    fclose(f);
    int fd = open(path, O_RDONLY);
    cr_assert(fd >= 0);
    cr_assert_not(read_header_from_fd(fd, &hdr));
    close(fd);
    unlink(path);
}

