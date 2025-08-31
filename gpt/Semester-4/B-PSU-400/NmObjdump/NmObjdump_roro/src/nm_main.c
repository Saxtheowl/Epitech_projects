/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** my_nm main
*/

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "common.h"

int nm_symbols(file_t *f);

static int nm_member_cb(const char *ar_path, const ar_member_t *m, void *ctx)
{
    (void)ctx;
    file_t f;
    memset(&f, 0, sizeof(f));
    f.path = ar_path;
    f.data = (unsigned char *)m->data;
    f.size = m->size;
    if (f.size >= 4 && f.data[0] == 0x7f && f.data[1] == 'E' && f.data[2] == 'L' && f.data[3] == 'F') {
        unsigned char cls = f.data[4];
        if (cls == ELFCLASS64) {
            f.kind = BIN_ELF64;
            f.u.e64.eh = (Elf64_Ehdr *)f.data;
            f.u.e64.sh = (Elf64_Shdr *)(f.data + f.u.e64.eh->e_shoff);
            f.u.e64.shnum = f.u.e64.eh->e_shnum;
        } else if (cls == ELFCLASS32) {
            f.kind = BIN_ELF32;
        }
        printf("\n%s(%s):\n", ar_path, m->name);
        nm_symbols(&f);
    }
    return 0;
}

static int proc_one(const char *path, int print_header)
{
    file_t f;
    if (open_file(path, &f) != 0) {
        fprintf(stderr, "%s: Invalid file\n", path);
        return 84;
    }
    if (f.kind == BIN_ELF32 || f.kind == BIN_ELF64) {
        if (print_header)
            printf("\n%s:\n", path);
        nm_symbols(&f);
    } else if (f.kind == BIN_AR) {
        ar_iterate(&f, nm_member_cb, NULL);
    }
    close_file(&f);
    return 0;
}

int main(int ac, char **av)
{
    int i;
    int st = 0;

    if (ac < 2)
        return proc_one("a.out", 0);
    for (i = 1; i < ac; ++i)
        st |= proc_one(av[i], ac > 2);
    return st;
}
