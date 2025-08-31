/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Tests for minimal assembler
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int read_be32(int fd)
{
    unsigned char b[4];
    if (read(fd, b, 4) != 4) return -1;
    return (int)((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
}

Test(robot, make_simple_cor)
{
    int rc = system("./robot_assembler -n \"NAME\" -c \"COMM\" -o test.cor 01:02:03");
    cr_assert_eq(rc, 0);
    int fd = open("test.cor", O_RDONLY);
    cr_assert(fd >= 0);
    cr_assert_eq(read_be32(fd), 0x00ea83f3);
    close(fd);
    unlink("test.cor");
}

