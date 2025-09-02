/*
** EPITECH PROJECT, 2025
** NmObjdump
** File description:
** Header for nm and objdump tools
*/

#ifndef NM_OBJDUMP_H_
#define NM_OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ERROR_EXIT 84

typedef struct {
    void *data;
    size_t size;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
    char *shstrtab;
    int is_64bit;
} elf_file_t;

typedef struct {
    uint64_t value;
    char type;
    const char *name;
} symbol_t;

int nm_main(int argc, char **argv);
int objdump_main(int argc, char **argv);

int load_elf_file(const char *filename, elf_file_t *elf);
void unload_elf_file(elf_file_t *elf);
int is_elf_file(const void *data);

int process_nm_file(const char *filename);
int process_objdump_file(const char *filename);

int extract_symbols(elf_file_t *elf, symbol_t **symbols, size_t *count);
void sort_symbols(symbol_t *symbols, size_t count);
char get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr);
void print_nm_symbols(symbol_t *symbols, size_t count, const char *filename);

void print_objdump_header(elf_file_t *elf, const char *filename);
void print_objdump_sections(elf_file_t *elf);
void print_objdump_symbols(elf_file_t *elf);

void print_error(const char *program, const char *message);

#endif /* !NM_OBJDUMP_H_ */