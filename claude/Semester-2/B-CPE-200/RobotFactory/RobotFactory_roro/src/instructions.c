/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Instruction definitions and operations table
*/

#include "asm.h"
#include "op.h"

op_t op_tab[17] = {
    {"live", 1, {T_DIR, 0, 0, 0}, 0x01, 10, "alive", 0, 0},
    {"ld", 2, {T_DIR | T_IND, T_REG, 0, 0}, 0x02, 5, "load", 1, 0},
    {"st", 2, {T_REG, T_IND | T_REG, 0, 0}, 0x03, 5, "store", 1, 0},
    {"add", 3, {T_REG, T_REG, T_REG, 0}, 0x04, 10, "addition", 1, 0},
    {"sub", 3, {T_REG, T_REG, T_REG, 0}, 0x05, 10, "soustraction", 1, 0},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG, 0}, 0x06, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0}, 0x07, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG, 0}, 0x08, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
    {"zjmp", 1, {T_DIR, 0, 0, 0}, 0x09, 20, "jump if zero", 0, 1},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 0x0a, 25, "load index", 1, 1},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG, 0}, 0x0b, 25, "store index", 1, 1},
    {"fork", 1, {T_DIR, 0, 0, 0}, 0x0c, 800, "fork", 0, 1},
    {"lld", 2, {T_DIR | T_IND, T_REG, 0, 0}, 0x0d, 10, "long load", 1, 0},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG, 0}, 0x0e, 50, "long load index", 1, 1},
    {"lfork", 1, {T_DIR, 0, 0, 0}, 0x0f, 1000, "long fork", 0, 1},
    {"aff", 1, {T_REG, 0, 0, 0}, 0x10, 2, "aff", 1, 0},
    {0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0}
};

op_t *get_operation(char *mnemonic)
{
    int i = 0;
    
    if (!mnemonic)
        return NULL;
    
    while (op_tab[i].mnemonique) {
        if (strcmp(op_tab[i].mnemonique, mnemonic) == 0)
            return &op_tab[i];
        i++;
    }
    
    return NULL;
}

int is_valid_register(char *param)
{
    int reg_num;
    
    if (!param || param[0] != 'r')
        return 0;
    
    reg_num = atoi(param + 1);
    return (reg_num >= 1 && reg_num <= REG_NUMBER);
}

int is_direct_param(char *param)
{
    if (!param || param[0] != DIRECT_CHAR)
        return 0;
    
    return 1;
}

int is_indirect_param(char *param)
{
    char *endptr;
    
    if (!param)
        return 0;
    
    if (param[0] == DIRECT_CHAR || param[0] == 'r')
        return 0;
    
    strtol(param, &endptr, 10);
    if (*endptr == '\0')
        return 1;
    
    return 1;
}