/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Header file for assembler
*/

#ifndef ASM_H_
#define ASM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define COREWAR_EXEC_MAGIC 0xea83f3
#define MAX_ARGS_NUMBER 4
#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

// From op.h definitions
#define T_REG 1
#define T_DIR 2
#define T_IND 4
#define T_LAB 8

#define REG_CODE 1
#define DIR_CODE 2
#define IND_CODE 3

#define REG_SIZE 4
#define IND_SIZE 2

typedef char args_type_t;

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
    char coding_byte;
    int dir_size;
} op_t;

typedef struct header_s {
    unsigned int magic;
    char prog_name[PROG_NAME_LENGTH + 1];
    unsigned int prog_size;
    char comment[COMMENT_LENGTH + 1];
} header_t;

typedef struct label_s {
    char *name;
    int position;
    struct label_s *next;
} label_t;

typedef struct instruction_s {
    op_t *op;
    char **args;
    int arg_count;
    int position;
    unsigned char coding_byte;
    struct instruction_s *next;
} instruction_t;

typedef struct asm_s {
    header_t header;
    instruction_t *instructions;
    label_t *labels;
    char *input_file;
    char *output_file;
    int current_pos;
} asm_t;

// op.c
extern op_t op_tab[];

// Main functions
int parse_arguments(int ac, char **av, asm_t *assembler);
void print_usage(void);
int parse_file(asm_t *assembler);
int generate_bytecode(asm_t *assembler);

// Parser functions
int parse_header(FILE *file, header_t *header);
int parse_instruction_line(char *line, asm_t *assembler);
int parse_label(char *line, asm_t *assembler);

// Assembler functions
int assemble_file(asm_t *assembler);
void write_header(FILE *file, header_t *header);
void write_instructions(FILE *file, asm_t *assembler);

// Bytecode functions
int calculate_instruction_size(instruction_t *inst);
unsigned char generate_coding_byte(instruction_t *inst);
int encode_parameter(char *param, op_t *op, int param_index, 
                    unsigned char *buffer, asm_t *assembler);

// Instruction functions
op_t *get_operation(char *mnemonic);
int is_valid_register(char *param);
int is_direct_param(char *param);
int is_indirect_param(char *param);

// Label functions
void add_label(asm_t *assembler, char *name, int position);
label_t *find_label(asm_t *assembler, char *name);
int resolve_label_value(asm_t *assembler, char *label_name, int current_pos);

// Header functions
int extract_name(char *line, char *name);
int extract_comment(char *line, char *comment);

// Utility functions
char *trim_whitespace(char *str);
int is_label_line(char *line);
int is_comment_line(char *line);
int is_empty_line(char *line);
void free_assembler(asm_t *assembler);
void write_big_endian_int(FILE *file, unsigned int value);
void write_big_endian_short(FILE *file, unsigned short value);

#endif /* !ASM_H_ */