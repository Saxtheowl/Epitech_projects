/*
** EPITECH PROJECT, 2025
** ftrace
** File description:
** Symbol table management (simplified version without libelf)
*/

#include "ftrace.h"

static symbol_t *add_symbol(symbol_t *head, const char *name, unsigned long addr)
{
    symbol_t *new_symbol = malloc(sizeof(symbol_t));

    if (!new_symbol)
        return head;
    
    new_symbol->name = strdup(name);
    if (!new_symbol->name) {
        free(new_symbol);
        return head;
    }
    
    new_symbol->address = addr;
    new_symbol->next = head;
    return new_symbol;
}

int load_symbols(ftrace_t *ftrace)
{
    char buffer[1024];
    FILE *fp;
    char *cmd;
    char name[256];
    unsigned long addr;
    char type;

    cmd = malloc(strlen("nm ") + strlen(ftrace->binary_path) + 1);
    if (!cmd)
        return -1;
    
    sprintf(cmd, "nm %s", ftrace->binary_path);
    fp = popen(cmd, "r");
    free(cmd);
    
    if (!fp)
        return -1;

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (sscanf(buffer, "%lx %c %255s", &addr, &type, name) == 3) {
            if (type == 'T' || type == 't') {
                ftrace->symbols = add_symbol(ftrace->symbols, name, addr);
            }
        }
    }

    pclose(fp);
    return 0;
}

symbol_t *find_symbol(symbol_t *symbols, unsigned long addr)
{
    symbol_t *current = symbols;
    symbol_t *best_match = NULL;
    unsigned long min_distance = ULONG_MAX;

    while (current) {
        if (current->address <= addr) {
            unsigned long distance = addr - current->address;
            if (distance < min_distance) {
                min_distance = distance;
                best_match = current;
            }
        }
        current = current->next;
    }

    if (best_match && min_distance < 1000)
        return best_match;
    
    return NULL;
}

void free_symbols(symbol_t *symbols)
{
    while (symbols) {
        symbol_t *next = symbols->next;
        free(symbols->name);
        free(symbols);
        symbols = next;
    }
}