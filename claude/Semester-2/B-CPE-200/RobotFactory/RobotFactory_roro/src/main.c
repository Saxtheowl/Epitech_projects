/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Main function for assembler
*/

#include "asm.h"

static void init_assembler(asm_t *assembler)
{
    assembler->header.magic = COREWAR_EXEC_MAGIC;
    assembler->header.prog_name[0] = '\0';
    assembler->header.prog_size = 0;
    assembler->header.comment[0] = '\0';
    assembler->instructions = NULL;
    assembler->labels = NULL;
    assembler->input_file = NULL;
    assembler->output_file = NULL;
    assembler->current_pos = 0;
}

int main(int ac, char **av)
{
    asm_t assembler;
    
    init_assembler(&assembler);
    
    if (parse_arguments(ac, av, &assembler) != 0) {
        print_usage();
        return 84;
    }
    
    if (parse_file(&assembler) != 0) {
        free_assembler(&assembler);
        return 84;
    }
    
    if (generate_bytecode(&assembler) != 0) {
        free_assembler(&assembler);
        return 84;
    }
    
    printf("Writing output program to %s\n", assembler.output_file);
    
    free_assembler(&assembler);
    return 0;
}