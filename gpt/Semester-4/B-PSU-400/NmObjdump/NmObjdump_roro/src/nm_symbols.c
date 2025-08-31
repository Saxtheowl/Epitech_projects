/*
** EPITECH PROJECT, 2025
** NmObjdump_roro
** File description:
** my_nm symbols
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include <ctype.h>

typedef struct sym_s {
    char type;
    char *name;
    unsigned long value;
} sym_t;

static int cmp_sym(const void *a, const void *b)
{
    const sym_t *sa = a;
    const sym_t *sb = b;
    return strcmp(sa->name, sb->name);
}

static char type_from64(const Elf64_Sym *sym, const Elf64_Shdr *shdrs)
{
    unsigned char bind = ELF64_ST_BIND(sym->st_info);
    unsigned char type = ELF64_ST_TYPE(sym->st_info);
    char c = '?';
    if (bind == STB_WEAK) {
        if (type == STT_OBJECT)
            c = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V';
        else
            c = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W';
        return c;
    }
    if (sym->st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym->st_shndx == SHN_ABS)
        c = 'A';
    else if (sym->st_shndx == SHN_COMMON)
        c = 'C';
    else {
        const Elf64_Shdr *sh = &shdrs[sym->st_shndx];
        if (sh->sh_type == SHT_NOBITS && (sh->sh_flags & SHF_ALLOC))
            c = 'B';
        else if (sh->sh_flags & SHF_EXECINSTR)
            c = 'T';
        else if ((sh->sh_flags & SHF_ALLOC) && (sh->sh_flags & SHF_WRITE))
            c = 'D';
        else if ((sh->sh_flags & SHF_ALLOC) && !(sh->sh_flags & SHF_WRITE))
            c = 'R';
        else if (type == STT_OBJECT)
            c = 'D';
        else
            c = 'T';
    }
    if (bind == STB_LOCAL && c != '?')
        c = (char)tolower(c);
    return c;
}

static int nm_elf64(file_t *f)
{
    size_t i;
    Elf64_Shdr *shdrs = f->u.e64.sh;
    (void)f->u.e64.eh;
    sym_t *list = NULL;
    size_t nlist = 0;
    size_t cap = 0;
    for (i = 0; i < f->u.e64.shnum; ++i) {
        const Elf64_Shdr *sh = &shdrs[i];
        if (sh->sh_type != SHT_SYMTAB && sh->sh_type != SHT_DYNSYM)
            continue;
        const unsigned char *symtab = f->data + sh->sh_offset;
        const Elf64_Shdr *strsh = &shdrs[sh->sh_link];
        const char *strtab = (const char *)(f->data + strsh->sh_offset);
        size_t nsyms = sh->sh_size / sh->sh_entsize;
        size_t j;
        for (j = 0; j < nsyms; ++j) {
            const Elf64_Sym *s = (const Elf64_Sym *)(symtab + j * sh->sh_entsize);
            if (ELF64_ST_TYPE(s->st_info) == STT_FILE)
                continue;
            const char *name = strtab + s->st_name;
            if (!name || !*name)
                continue;
            if (cap == nlist) {
                cap = cap ? cap * 2 : 64;
                list = realloc(list, cap * sizeof(sym_t));
            }
            list[nlist].name = strdup(name);
            list[nlist].value = s->st_value;
            list[nlist].type = type_from64(s, shdrs);
            nlist++;
        }
    }
    qsort(list, nlist, sizeof(sym_t), cmp_sym);
    for (i = 0; i < nlist; ++i) {
        if (list[i].type == 'U' || list[i].type == 'u' ||
            list[i].type == 'w' || list[i].type == 'v')
            printf("%16s %c %s\n", "", list[i].type, list[i].name);
        else
            printf("%016lx %c %s\n", (unsigned long)list[i].value, list[i].type, list[i].name);
        free(list[i].name);
    }
    free(list);
    return 0;
}

static char type_from32(const Elf32_Sym *sym, const Elf32_Shdr *shdrs)
{
    unsigned char bind = ELF32_ST_BIND(sym->st_info);
    unsigned char type = ELF32_ST_TYPE(sym->st_info);
    char c = '?';
    if (bind == STB_WEAK) {
        if (type == STT_OBJECT)
            c = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V';
        else
            c = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W';
        return c;
    }
    if (sym->st_shndx == SHN_UNDEF)
        c = 'U';
    else if (sym->st_shndx == SHN_ABS)
        c = 'A';
    else if (sym->st_shndx == SHN_COMMON)
        c = 'C';
    else {
        const Elf32_Shdr *sh = &shdrs[sym->st_shndx];
        if (sh->sh_type == SHT_NOBITS && (sh->sh_flags & SHF_ALLOC))
            c = 'B';
        else if (sh->sh_flags & SHF_EXECINSTR)
            c = 'T';
        else if ((sh->sh_flags & SHF_ALLOC) && (sh->sh_flags & SHF_WRITE))
            c = 'D';
        else if ((sh->sh_flags & SHF_ALLOC) && !(sh->sh_flags & SHF_WRITE))
            c = 'R';
        else if (type == STT_OBJECT)
            c = 'D';
        else
            c = 'T';
    }
    if (bind == STB_LOCAL && c != '?')
        c = (char)tolower(c);
    return c;
}

static int nm_elf32(file_t *f)
{
    const Elf32_Shdr *shdrs;
    const Elf32_Ehdr *eh;
    sym_t *list = NULL;
    size_t nlist = 0;
    size_t cap = 0;
    size_t i;

    eh = f->u.e32.eh; (void)eh;
    shdrs = f->u.e32.sh;
    for (i = 0; i < f->u.e32.shnum; ++i) {
        const Elf32_Shdr *sh = &shdrs[i];
        if (sh->sh_type != SHT_SYMTAB && sh->sh_type != SHT_DYNSYM)
            continue;
        const unsigned char *symtab = f->data + sh->sh_offset;
        const Elf32_Shdr *strsh = &shdrs[sh->sh_link];
        const char *strtab = (const char *)(f->data + strsh->sh_offset);
        size_t nsyms = sh->sh_size / sh->sh_entsize;
        size_t j;
        for (j = 0; j < nsyms; ++j) {
            const Elf32_Sym *s = (const Elf32_Sym *)(symtab + j * sh->sh_entsize);
            if (ELF32_ST_TYPE(s->st_info) == STT_FILE)
                continue;
            const char *name = strtab + s->st_name;
            if (!name || !*name)
                continue;
            if (cap == nlist) {
                cap = cap ? cap * 2 : 64;
                list = realloc(list, cap * sizeof(sym_t));
            }
            list[nlist].name = strdup(name);
            list[nlist].value = (unsigned long)s->st_value;
            list[nlist].type = type_from32(s, shdrs);
            nlist++;
        }
    }
    qsort(list, nlist, sizeof(sym_t), cmp_sym);
    for (i = 0; i < nlist; ++i) {
        if (list[i].type == 'U' || list[i].type == 'u' ||
            list[i].type == 'w' || list[i].type == 'v')
            printf("%8s %c %s\n", "", list[i].type, list[i].name);
        else
            printf("%08lx %c %s\n", (unsigned long)list[i].value, list[i].type, list[i].name);
        free(list[i].name);
    }
    free(list);
    return 0;
}

int nm_symbols(file_t *f)
{
    if (f->kind == BIN_ELF64)
        return nm_elf64(f);
    if (f->kind == BIN_ELF32)
        return nm_elf32(f);
    return 0;
}
