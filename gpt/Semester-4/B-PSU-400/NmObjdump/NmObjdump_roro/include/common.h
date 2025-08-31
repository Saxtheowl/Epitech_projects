/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** common header
*/

#ifndef COMMON_H
    #define COMMON_H

    #include <elf.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef enum {
        BIN_UNKNOWN = 0,
        BIN_ELF32,
        BIN_ELF64,
        BIN_AR
    } bin_kind_t;

    typedef struct file_s {
        const char *path;
        int fd;
        unsigned char *data;
        size_t size;
        bin_kind_t kind;
        union {
            struct { Elf32_Ehdr *eh; Elf32_Shdr *sh; size_t shnum; } e32;
            struct { Elf64_Ehdr *eh; Elf64_Shdr *sh; size_t shnum; } e64;
        } u;
    } file_t;

    int open_file(const char *path, file_t *out);
    void close_file(file_t *f);
    void *xmalloc(size_t n);
    int is_ar(const unsigned char *p, size_t n);

    typedef struct ar_member_s {
        const char *name;
        const unsigned char *data;
        size_t size;
    } ar_member_t;

    typedef int (*ar_iter_cb)(const char *ar_path, const ar_member_t *m, void *ctx);
    int ar_iterate(const file_t *ar, ar_iter_cb cb, void *ctx);

#endif /* COMMON_H */
