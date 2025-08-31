/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** my_objdump -s section hexdump
*/

#include <ctype.h>
#include <string.h>
#include "common.h"

static void dump_bytes64(const unsigned char *p, unsigned long addr, size_t n)
{
    size_t i;
    printf(" %016lx ", addr);
    for (i = 0; i < 16; ++i) {
        if (i < n)
            printf(" %02x", p[i]);
        else
            printf("   ");
    }
    printf("  ");
    for (i = 0; i < n; ++i) {
        unsigned char c = p[i];
        printf("%c", isprint(c) ? c : '.');
    }
    printf("\n");
}

static void dump_elf64(const file_t *f)
{
    const Elf64_Ehdr *eh = f->u.e64.eh;
    const Elf64_Shdr *sh = f->u.e64.sh;
    const char *shstr = (const char *)(f->data + sh[eh->e_shstrndx].sh_offset);
    size_t i;
    for (i = 0; i < f->u.e64.shnum; ++i) {
        const Elf64_Shdr *s = &sh[i];
        if (s->sh_size == 0)
            continue;
        const char *name = shstr + s->sh_name;
        const unsigned char *p = f->data + s->sh_offset;
        size_t off = 0;
        printf("Contents of section %s:\n", name);
        while (off < s->sh_size) {
            size_t chunk = (s->sh_size - off) < 16 ? (s->sh_size - off) : 16;
            dump_bytes64(p + off, (unsigned long)(s->sh_addr + off), chunk);
            off += chunk;
        }
        printf("\n");
    }
}

static void dump_bytes32(const unsigned char *p, unsigned long addr, size_t n)
{
    size_t i;
    printf(" %08lx ", addr);
    for (i = 0; i < 16; ++i) {
        if (i < n)
            printf(" %02x", p[i]);
        else
            printf("   ");
    }
    printf("  ");
    for (i = 0; i < n; ++i) {
        unsigned char c = p[i];
        printf("%c", isprint(c) ? c : '.');
    }
    printf("\n");
}

static void dump_elf32(const file_t *f)
{
    const Elf32_Ehdr *eh = f->u.e32.eh;
    const Elf32_Shdr *sh = f->u.e32.sh;
    const char *shstr = (const char *)(f->data + sh[eh->e_shstrndx].sh_offset);
    size_t i;
    for (i = 0; i < f->u.e32.shnum; ++i) {
        const Elf32_Shdr *s = &sh[i];
        if (s->sh_size == 0)
            continue;
        const char *name = shstr + s->sh_name;
        const unsigned char *p = f->data + s->sh_offset;
        size_t off = 0;
        printf("Contents of section %s:\n", name);
        while (off < s->sh_size) {
            size_t chunk = (s->sh_size - off) < 16 ? (s->sh_size - off) : 16;
            dump_bytes32(p + off, (unsigned long)(s->sh_addr + off), chunk);
            off += chunk;
        }
        printf("\n");
    }
}

int objdump_dump_sections(file_t *f)
{
    if (f->kind == BIN_ELF64)
        dump_elf64(f);
    else if (f->kind == BIN_ELF32)
        dump_elf32(f);
    return 0;
}
