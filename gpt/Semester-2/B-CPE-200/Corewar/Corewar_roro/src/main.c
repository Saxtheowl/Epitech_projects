/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** Minimal CLI to validate champion headers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corewar.h"
#include "vm.h"

static void print_usage(const char *bin)
{
    printf("Usage: %s [--cycles N] <champion.cor> [<champion.cor> ...]\n", bin);
}

int main(int argc, char **argv)
{
    int i;
    champion_t *champs;
    unsigned char *arena;
    int cycles = 64;

    if (argc < 2) {
        print_usage(argv[0]);
        return 84;
    }
    /* parse optional --cycles */
    i = 1;
    if (i + 1 < argc && strcmp(argv[i], "--cycles") == 0) {
        cycles = atoi(argv[i + 1]);
        if (cycles <= 0) cycles = 64;
        i += 2;
    }
    if (i >= argc) { print_usage(argv[0]); return 84; }
    champs = calloc((size_t)(argc - i), sizeof(*champs));
    arena = calloc(MEM_SIZE, 1);
    if (!champs || !arena) return 84;
    {
        int ci = 0;
        while (i < argc) {
            if (!load_champion_full(argv[i], &champs[ci])) {
                fprintf(stderr, "Failed to load %s\n", argv[i]);
                free(arena); free(champs); return 84;
            }
            printf("Loaded: %s (%d bytes)\n", champs[ci].hdr.prog_name, champs[ci].hdr.prog_size);
            ci++; i++;
        }
        /* place with loaded count */
        if (ci == 0 || !place_champions(arena, MEM_SIZE, champs, ci)) {
        fprintf(stderr, "Placement error\n");
        free(arena); free(champs); return 84;
        }
    }
    /* print first few bytes of each champion placement */
    {
        int count = 0; while (champs[count].code) { count++; }
        for (i = 0; i < count; ++i)
            printf("Champion %d at 0x%04X\n", i + 1, champs[i].load_addr);
    }
    {
        vm_t vm;
        /* recompute count */
        int count = 0; while (champs[count].code) { count++; }
        if (!vm_init(&vm, champs, count)) {
            fprintf(stderr, "VM init failed\n");
            free(arena); for (i = 0; i < argc - 1; ++i) free(champs[i].code); free(champs); return 84;
        }
        /* Run cycles */
        vm_run(&vm, cycles);
        free(vm.procs);
    }
    free(arena);
    for (i = 0; i < argc - 1; ++i) free(champs[i].code);
    free(champs);
    return 0;
}
