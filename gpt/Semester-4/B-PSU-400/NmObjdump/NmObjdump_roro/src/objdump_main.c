/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** my_objdump main (-fs)
*/

#include <string.h>
#include "common.h"

int objdump_file(file_t *f);
static int parse_opts(int ac, char **av, int *first_file)
{
    int i = 1;
    int saw_f = 0;
    int saw_s = 0;
    while (i < ac && av[i][0] == '-') {
        if (strcmp(av[i], "-fs") == 0) {
            saw_f = 1; saw_s = 1; i += 1;
            continue;
        }
        if (strcmp(av[i], "-f") == 0) { saw_f = 1; i += 1; continue; }
        if (strcmp(av[i], "-s") == 0) { saw_s = 1; i += 1; continue; }
        return 84; /* unsupported option */
    }
    (void)saw_f; (void)saw_s; /* we always output both */
    *first_file = i;
    return 0;
}
static int od_member_cb(const char *ar_path, const ar_member_t *m, void *ctx)
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
        objdump_file(&f);
    }
    return 0;
}

static int proc_one(const char *path)
{
    file_t f;
    if (open_file(path, &f) != 0) {
        fprintf(stderr, "%s: Invalid file\n", path);
        return 84;
    }
    if (f.kind == BIN_AR) {
        int rc = ar_iterate(&f, od_member_cb, NULL);
        close_file(&f);
        return rc;
    } else {
        int rc = objdump_file(&f);
        close_file(&f);
        return rc;
    }
}

int main(int ac, char **av)
{
    int st = 0;
    int i;
    int first;
    if (ac < 2)
        return proc_one("a.out");
    if (parse_opts(ac, av, &first) == 84)
        return 84;
    if (first >= ac)
        return 84;
    for (i = first; i < ac; ++i)
        st |= proc_one(av[i]);
    return st;
}
