/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** my_objdump -f header
*/

#include <string.h>
#include "common.h"

static const char *fmt_from64(const Elf64_Ehdr *e)
{
    if (e->e_ident[EI_CLASS] == ELFCLASS64 && e->e_machine == EM_X86_64)
        return "elf64-x86-64";
    if (e->e_ident[EI_CLASS] == ELFCLASS32 && e->e_machine == EM_386)
        return "elf32-i386";
    return "elf";
}

static const char *arch_from64(const Elf64_Ehdr *e)
{
    if (e->e_machine == EM_X86_64)
        return "i386:x86-64";
    if (e->e_machine == EM_386)
        return "i386";
    return "unknown";
}

static unsigned flags_from64(const file_t *f)
{
    /* simplistic flags estimation */
    unsigned flags = 0;
    size_t i;
    const Elf64_Ehdr *eh = f->u.e64.eh;
    const Elf64_Shdr *sh = f->u.e64.sh;
    if (eh->e_type == ET_EXEC)
        flags |= 0x0002; /* EXEC_P */
    if (eh->e_type == ET_DYN)
        flags |= 0x0040; /* DYNAMIC */
    for (i = 0; i < f->u.e64.shnum; ++i) {
        if (sh[i].sh_type == SHT_SYMTAB)
            flags |= 0x0010; /* HAS_SYMS */
        if (sh[i].sh_type == SHT_RELA || sh[i].sh_type == SHT_REL)
            flags |= 0x0001; /* HAS_RELOC */
    }
    return flags;
}

static void print_flags_line(unsigned fl)
{
    int first = 1;
    if (fl & 0x0001) { printf("HAS_RELOC"); first = 0; }
    if (fl & 0x0002) { printf(first ? "EXEC_P" : ", EXEC_P"); first = 0; }
    if (fl & 0x0010) { printf(first ? "HAS_SYMS" : ", HAS_SYMS"); first = 0; }
    if (fl & 0x0040) { printf(first ? "DYNAMIC" : ", DYNAMIC"); first = 0; }
    if (fl & 0x0100) { printf(first ? "D_PAGED" : ", D_PAGED"); first = 0; }
    printf("\n");
}

static const char *fmt_from32(const Elf32_Ehdr *e)
{
    if (e->e_ident[EI_CLASS] == ELFCLASS64 && e->e_machine == EM_X86_64)
        return "elf64-x86-64";
    if (e->e_ident[EI_CLASS] == ELFCLASS32 && e->e_machine == EM_386)
        return "elf32-i386";
    return "elf";
}

static const char *arch_from32(const Elf32_Ehdr *e)
{
    if (e->e_machine == EM_X86_64)
        return "i386:x86-64";
    if (e->e_machine == EM_386)
        return "i386";
    return "unknown";
}

static unsigned flags_from32(const file_t *f)
{
    unsigned flags = 0;
    size_t i;
    const Elf32_Ehdr *eh = f->u.e32.eh;
    const Elf32_Shdr *sh = f->u.e32.sh;
    if (eh->e_type == ET_EXEC)
        flags |= 0x0002; /* EXEC_P */
    if (eh->e_type == ET_DYN)
        flags |= 0x0040; /* DYNAMIC */
    for (i = 0; i < f->u.e32.shnum; ++i) {
        if (sh[i].sh_type == SHT_SYMTAB)
            flags |= 0x0010; /* HAS_SYMS */
        if (sh[i].sh_type == SHT_RELA || sh[i].sh_type == SHT_REL)
            flags |= 0x0001; /* HAS_RELOC */
    }
    return flags;
}

int objdump_dump_sections(file_t *f);

int objdump_file(file_t *f)
{
    if (f->kind == BIN_ELF64) {
        printf("%s:     file format %s\n\n", f->path, fmt_from64(f->u.e64.eh));
        unsigned fl = flags_from64(f);
        printf("architecture: %s, flags 0x%08x:\n", arch_from64(f->u.e64.eh), fl);
        print_flags_line(fl);
        printf("start address 0x%016lx\n\n", (unsigned long)f->u.e64.eh->e_entry);
        return objdump_dump_sections(f);
    } else if (f->kind == BIN_ELF32) {
        unsigned fl = flags_from32(f);
        printf("%s:     file format %s\n\n", f->path, fmt_from32(f->u.e32.eh));
        printf("architecture: %s, flags 0x%08x:\n", arch_from32(f->u.e32.eh), fl);
        print_flags_line(fl);
        printf("start address 0x%08lx\n\n", (unsigned long)f->u.e32.eh->e_entry);
        return objdump_dump_sections(f);
    }
    return 0;
}
