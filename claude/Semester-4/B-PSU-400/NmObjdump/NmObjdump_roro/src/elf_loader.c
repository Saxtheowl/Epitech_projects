/*
** EPITECH PROJECT, 2025
** NmObjdump
** File description:
** ELF file loading and validation
*/

#include "nm_objdump.h"

int is_elf_file(const void *data)
{
    const unsigned char *magic = (const unsigned char *)data;
    
    return (magic[0] == 0x7f && magic[1] == 'E' && 
            magic[2] == 'L' && magic[3] == 'F');
}

int load_elf_file(const char *filename, elf_file_t *elf)
{
    int fd;
    struct stat st;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_error("nm", "No such file");
        return -1;
    }
    
    if (fstat(fd, &st) == -1) {
        close(fd);
        return -1;
    }
    
    elf->size = st.st_size;
    elf->data = mmap(NULL, elf->size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    
    if (elf->data == MAP_FAILED) {
        return -1;
    }
    
    if (!is_elf_file(elf->data)) {
        munmap(elf->data, elf->size);
        print_error("nm", "File format not recognized");
        return -1;
    }
    
    elf->ehdr = (Elf64_Ehdr *)elf->data;
    elf->is_64bit = (elf->ehdr->e_ident[EI_CLASS] == ELFCLASS64);
    
    if (!elf->is_64bit) {
        munmap(elf->data, elf->size);
        print_error("nm", "32-bit ELF not supported in this implementation");
        return -1;
    }
    
    elf->shdr = (Elf64_Shdr *)((char *)elf->data + elf->ehdr->e_shoff);
    
    if (elf->ehdr->e_shstrndx != SHN_UNDEF) {
        Elf64_Shdr *shstrtab_hdr = &elf->shdr[elf->ehdr->e_shstrndx];
        elf->shstrtab = (char *)elf->data + shstrtab_hdr->sh_offset;
    } else {
        elf->shstrtab = NULL;
    }
    
    return 0;
}

void unload_elf_file(elf_file_t *elf)
{
    if (elf->data && elf->data != MAP_FAILED) {
        munmap(elf->data, elf->size);
    }
    memset(elf, 0, sizeof(elf_file_t));
}