/*
** EPITECH PROJECT, 2024
** Corewar
** File description:
** Champion loading and management
*/

#include "corewar.h"

static int read_header(int fd, header_t *header)
{
    if (read(fd, header, sizeof(header_t)) != sizeof(header_t))
        return ERROR;
    
    // Convert from big-endian to host byte order
    header->magic = __builtin_bswap32(header->magic);
    header->prog_size = __builtin_bswap32(header->prog_size);
    
    if (header->magic != COREWAR_EXEC_MAGIC)
        return ERROR;
    if (header->prog_size <= 0 || header->prog_size > MEM_SIZE)
        return ERROR;
    
    return SUCCESS;
}

static int calculate_load_address(vm_t *vm, int specified_address)
{
    if (specified_address != -1)
        return specified_address % MEM_SIZE;
    
    // Distribute champions evenly in memory
    int spacing = MEM_SIZE / MAX_CHAMPIONS;
    return (vm->nb_champions * spacing) % MEM_SIZE;
}

int load_champion(vm_t *vm, char *filename, int champion_id, int load_address)
{
    int fd = open(filename, O_RDONLY);
    header_t header;
    champion_t *champion;

    if (fd == -1)
        return ERROR;
    
    if (read_header(fd, &header) == ERROR) {
        close(fd);
        return ERROR;
    }
    
    champion = malloc(sizeof(champion_t));
    if (!champion) {
        close(fd);
        return ERROR;
    }
    
    champion->id = champion_id;
    strncpy(champion->name, header.prog_name, PROG_NAME_LENGTH);
    champion->name[PROG_NAME_LENGTH] = '\0';
    strncpy(champion->comment, header.comment, COMMENT_LENGTH);
    champion->comment[COMMENT_LENGTH] = '\0';
    champion->prog_size = header.prog_size;
    champion->load_address = calculate_load_address(vm, load_address);
    champion->last_live = 0;
    
    champion->code = malloc(champion->prog_size);
    if (!champion->code) {
        free(champion);
        close(fd);
        return ERROR;
    }
    
    if (read(fd, champion->code, champion->prog_size) != champion->prog_size) {
        free(champion->code);
        free(champion);
        close(fd);
        return ERROR;
    }
    
    close(fd);
    vm->champions[vm->nb_champions++] = champion;
    return SUCCESS;
}