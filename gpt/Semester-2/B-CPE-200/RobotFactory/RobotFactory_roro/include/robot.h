/*
** EPITECH PROJECT, 2025
** RobotFactory
** File description:
** Prototypes for a minimal Corewar robot assembler
*/

#ifndef ROBOT_H
    #define ROBOT_H

int write_robot(const char *out_path, const char *name, const char *comment,
                const unsigned char *code, int code_size);
int hex_to_bytes(const char *hex, unsigned char *out, int max);

#endif /* ROBOT_H */

