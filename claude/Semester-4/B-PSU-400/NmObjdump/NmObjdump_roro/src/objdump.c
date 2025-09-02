/*
** EPITECH PROJECT, 2025
** NmObjdump
** File description:
** objdump command implementation
*/

#include "nm_objdump.h"

void print_objdump_header(elf_file_t *elf, const char *filename)
{
    printf("\n%s:     file format elf64-x86-64\n", filename);
    printf("architecture: i386:x86-64, flags 0x%08x:\n", elf->ehdr->e_flags);
    
    if (elf->ehdr->e_type == ET_EXEC)
        printf("EXEC_P");
    else if (elf->ehdr->e_type == ET_DYN)
        printf("HAS_RELOC, EXEC_P, HAS_LINENO, HAS_DEBUG, HAS_SYMS, DYNAMIC, WP_TEXT, D_PAGED");
    else if (elf->ehdr->e_type == ET_REL)
        printf("HAS_RELOC, HAS_SYMS");
    
    printf("\nstart address 0x%016lx\n\n", elf->ehdr->e_entry);
}

void print_objdump_sections(elf_file_t *elf)
{
    size_t i;
    
    printf("Sections:\n");
    printf("Idx Name          Size      VMA               LMA               File off  Algn\n");
    
    for (i = 0; i < elf->ehdr->e_shnum; i++) {
        Elf64_Shdr *section = &elf->shdr[i];
        const char *name = "";
        
        if (elf->shstrtab && section->sh_name)
            name = elf->shstrtab + section->sh_name;
        
        if (section->sh_type != SHT_NULL) {
            printf("%3zu %-13s %08lx  %016lx  %016lx  %08lx  2**%d\n",
                   i, name,
                   section->sh_size,
                   section->sh_addr,
                   section->sh_addr,
                   section->sh_offset,
                   __builtin_ctzl(section->sh_addralign ? section->sh_addralign : 1));
            
            if (section->sh_flags & SHF_ALLOC)
                printf("                  CONTENTS");
            if (section->sh_flags & SHF_ALLOC)
                printf(", ALLOC");
            if (section->sh_type != SHT_NOBITS && section->sh_size > 0)
                printf(", LOAD");
            if (section->sh_flags & SHF_EXECINSTR)
                printf(", CODE");
            if (section->sh_flags & SHF_WRITE)
                printf(", DATA");
            if (section->sh_type == SHT_REL || section->sh_type == SHT_RELA)
                printf(", RELOC");
            printf("\n");
        }
    }
}

void print_objdump_symbols(elf_file_t *elf)
{
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    size_t i;
    
    for (i = 0; i < elf->ehdr->e_shnum; i++) {
        if (elf->shdr[i].sh_type == SHT_SYMTAB) {
            symtab = &elf->shdr[i];
            strtab = &elf->shdr[symtab->sh_link];
            break;
        }
    }
    
    if (!symtab)
        return;
    
    size_t num_symbols = symtab->sh_size / symtab->sh_entsize;
    Elf64_Sym *sym_table = (Elf64_Sym *)((char *)elf->data + symtab->sh_offset);
    char *str_table = (char *)elf->data + strtab->sh_offset;
    
    printf("SYMBOL TABLE:\n");
    
    for (i = 0; i < num_symbols; i++) {
        const char *name = "";
        char bind_info[20];
        char type_info[20];
        
        if (sym_table[i].st_name != 0)
            name = str_table + sym_table[i].st_name;
        
        switch (ELF64_ST_BIND(sym_table[i].st_info)) {
            case STB_LOCAL: strcpy(bind_info, "l"); break;
            case STB_GLOBAL: strcpy(bind_info, "g"); break;
            case STB_WEAK: strcpy(bind_info, "w"); break;
            default: strcpy(bind_info, " "); break;
        }
        
        switch (ELF64_ST_TYPE(sym_table[i].st_info)) {
            case STT_NOTYPE: strcpy(type_info, ""); break;
            case STT_OBJECT: strcpy(type_info, "O"); break;
            case STT_FUNC: strcpy(type_info, "F"); break;
            case STT_SECTION: strcpy(type_info, ""); break;
            case STT_FILE: strcpy(type_info, ""); break;
            default: strcpy(type_info, ""); break;
        }
        
        if (sym_table[i].st_shndx == SHN_UNDEF)
            printf("%016lx %s %s\t%016lx %s\n",
                   sym_table[i].st_value, bind_info, type_info, sym_table[i].st_size, name);
        else
            printf("%016lx %s %s %s\t%016lx %s\n",
                   sym_table[i].st_value, bind_info, 
                   sym_table[i].st_shndx == SHN_ABS ? "*ABS*" : 
                   (elf->shstrtab && sym_table[i].st_shndx < elf->ehdr->e_shnum) ?
                   elf->shstrtab + elf->shdr[sym_table[i].st_shndx].sh_name : "",
                   type_info, sym_table[i].st_size, name);
    }
}

int process_objdump_file(const char *filename)
{
    elf_file_t elf;
    
    if (load_elf_file(filename, &elf) != 0)
        return ERROR_EXIT;
    
    print_objdump_header(&elf, filename);
    print_objdump_sections(&elf);
    printf("\n");
    print_objdump_symbols(&elf);
    
    unload_elf_file(&elf);
    return 0;
}

int objdump_main(int argc, char **argv)
{
    int i;
    int ret = 0;
    
    if (argc < 2) {
        if (process_objdump_file("a.out") != 0)
            ret = ERROR_EXIT;
    } else {
        for (i = 1; i < argc; i++) {
            if (process_objdump_file(argv[i]) != 0)
                ret = ERROR_EXIT;
        }
    }
    
    return ret;
}