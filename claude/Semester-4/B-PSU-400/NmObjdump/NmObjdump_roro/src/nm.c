/*
** EPITECH PROJECT, 2025
** NmObjdump
** File description:
** nm command implementation
*/

#include "nm_objdump.h"

char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
    char type = '?';
    
    if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
        return 'u';
    
    if (ELF64_ST_BIND(sym->st_info) == STB_WEAK) {
        if (ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
            return sym->st_shndx == SHN_UNDEF ? 'v' : 'V';
        return sym->st_shndx == SHN_UNDEF ? 'w' : 'W';
    }
    
    if (sym->st_shndx == SHN_UNDEF)
        return 'U';
    if (sym->st_shndx == SHN_ABS)
        return 'A';
    if (sym->st_shndx == SHN_COMMON)
        return 'C';
    
    if (sym->st_shndx < SHN_LORESERVE) {
        Elf64_Shdr *section = &shdr[sym->st_shndx];
        
        if (section->sh_type == SHT_NOBITS && 
            (section->sh_flags & SHF_ALLOC) &&
            (section->sh_flags & SHF_WRITE))
            type = 'B';
        else if ((section->sh_flags & SHF_ALLOC) && 
                 (section->sh_flags & SHF_WRITE))
            type = 'D';
        else if (section->sh_flags & SHF_ALLOC)
            type = section->sh_flags & SHF_EXECINSTR ? 'T' : 'R';
        else
            type = 'N';
    }
    
    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && type != '?')
        type += 32;
    
    return type;
}

int extract_symbols(elf_file_t *elf, symbol_t **symbols, size_t *count)
{
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    size_t i, j = 0;
    
    for (i = 0; i < elf->ehdr->e_shnum; i++) {
        if (elf->shdr[i].sh_type == SHT_SYMTAB) {
            symtab = &elf->shdr[i];
            strtab = &elf->shdr[symtab->sh_link];
            break;
        }
    }
    
    if (!symtab) {
        *symbols = NULL;
        *count = 0;
        return 0;
    }
    
    size_t num_symbols = symtab->sh_size / symtab->sh_entsize;
    Elf64_Sym *sym_table = (Elf64_Sym *)((char *)elf->data + symtab->sh_offset);
    char *str_table = (char *)elf->data + strtab->sh_offset;
    
    *symbols = malloc(num_symbols * sizeof(symbol_t));
    if (!*symbols)
        return -1;
    
    for (i = 0; i < num_symbols; i++) {
        if (sym_table[i].st_name == 0)
            continue;
        
        (*symbols)[j].value = sym_table[i].st_value;
        (*symbols)[j].type = get_symbol_type(&sym_table[i], elf->shdr);
        (*symbols)[j].name = str_table + sym_table[i].st_name;
        j++;
    }
    
    *count = j;
    return 0;
}

static int symbol_compare(const void *a, const void *b)
{
    const symbol_t *sym_a = (const symbol_t *)a;
    const symbol_t *sym_b = (const symbol_t *)b;
    
    return strcmp(sym_a->name, sym_b->name);
}

void sort_symbols(symbol_t *symbols, size_t count)
{
    qsort(symbols, count, sizeof(symbol_t), symbol_compare);
}

void print_nm_symbols(symbol_t *symbols, size_t count, const char *filename)
{
    size_t i;
    
    if (count == 0)
        return;
    
    (void)filename;
    for (i = 0; i < count; i++) {
        if (symbols[i].type == 'U' || symbols[i].type == 'w' || symbols[i].type == 'v')
            printf("                 %c %s\n", symbols[i].type, symbols[i].name);
        else
            printf("%016lx %c %s\n", symbols[i].value, symbols[i].type, symbols[i].name);
    }
}

int process_nm_file(const char *filename)
{
    elf_file_t elf;
    symbol_t *symbols;
    size_t count;
    
    if (load_elf_file(filename, &elf) != 0)
        return ERROR_EXIT;
    
    if (extract_symbols(&elf, &symbols, &count) != 0) {
        unload_elf_file(&elf);
        return ERROR_EXIT;
    }
    
    sort_symbols(symbols, count);
    print_nm_symbols(symbols, count, filename);
    
    free(symbols);
    unload_elf_file(&elf);
    return 0;
}

int nm_main(int argc, char **argv)
{
    int i;
    int ret = 0;
    
    if (argc < 2) {
        if (process_nm_file("a.out") != 0)
            ret = ERROR_EXIT;
    } else {
        for (i = 1; i < argc; i++) {
            if (process_nm_file(argv[i]) != 0)
                ret = ERROR_EXIT;
        }
    }
    
    return ret;
}