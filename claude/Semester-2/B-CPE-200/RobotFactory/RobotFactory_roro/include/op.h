/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** op.h - operations and constants for Corewar
*/

#ifndef OP_H_
#define OP_H_

#define MEM_SIZE (4*1024)
#define IDX_MOD (MEM_SIZE / 8)
#define CHAMP_MAX_SIZE (MEM_SIZE / 6)

#define COMMENT_CHAR '#'
#define LABEL_CHAR ':'
#define DIRECT_CHAR '%'
#define SEPARATOR_CHAR ','

#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"

#define REG_NUMBER 16

#define CYCLE_TO_DIE 1536
#define CYCLE_DELTA 50
#define NBR_LIVE 21
#define MAX_CHECKS 10

typedef char args_type_t;

#define T_REG 1
#define T_DIR 2
#define T_IND 4
#define T_LAB 8

#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048
#define COREWAR_EXEC_MAGIC 0xea83f3

#define REG_SIZE 4
#define IND_SIZE 2
#define DIR_SIZE REG_SIZE

#define OP_TAB_SIZE 16

#endif /* !OP_H_ */