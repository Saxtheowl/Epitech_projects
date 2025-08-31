/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Prototypes
*/

#ifndef COREWAR_H
    #define COREWAR_H

#include "op.h"

typedef struct {
    header_t hdr;
    unsigned char *code;
    int load_addr;
} champion_t;

int read_header_from_fd(int fd, header_t *hdr);
int load_champion_header(const char *path, header_t *hdr);
int load_champion_full(const char *path, champion_t *champ);
int place_champions(unsigned char *arena, int arena_size, champion_t *champs, int count);

#endif /* COREWAR_H */
