/*
** EPITECH PROJECT, 2024
** Fridge
** File description:
** Refrigerator ingredient management system
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_INGREDIENTS 8
#define MAX_LINE 1024

typedef struct {
    char *name;
    int quantity;
} ingredient_t;

typedef struct {
    ingredient_t ingredients[NUM_INGREDIENTS];
} fridge_t;

void init_fridge(fridge_t *fridge)
{
    char *names[] = {"tomato", "dough", "onion", "pasta", "olive", "pepper", "ham", "cheese"};
    int i;
    
    for (i = 0; i < NUM_INGREDIENTS; i++) {
        fridge->ingredients[i].name = names[i];
        fridge->ingredients[i].quantity = 50;
    }
}

int find_ingredient(fridge_t *fridge, char *name)
{
    int i;
    
    for (i = 0; i < NUM_INGREDIENTS; i++) {
        if (strcmp(fridge->ingredients[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int load_fridge(fridge_t *fridge)
{
    FILE *file = fopen(".save", "r");
    char buffer[MAX_LINE];
    char name[100];
    int quantity;
    int ingredient_idx;
    
    if (!file) {
        init_fridge(fridge);
        return 0;
    }
    
    init_fridge(fridge);
    
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "%s = %d", name, &quantity) == 2) {
            ingredient_idx = find_ingredient(fridge, name);
            if (ingredient_idx >= 0) {
                fridge->ingredients[ingredient_idx].quantity = quantity;
            }
        }
    }
    
    fclose(file);
    return 0;
}

void save_fridge(fridge_t *fridge)
{
    FILE *file = fopen(".save", "w");
    int i;
    
    if (!file)
        return;
    
    for (i = 0; i < NUM_INGREDIENTS; i++) {
        fprintf(file, "%s = %d\n", 
                fridge->ingredients[i].name, 
                fridge->ingredients[i].quantity);
    }
    
    fclose(file);
}

void disp_fridge(fridge_t *fridge)
{
    int i;
    
    for (i = 0; i < NUM_INGREDIENTS; i++) {
        printf("%s = %d\n", 
               fridge->ingredients[i].name, 
               fridge->ingredients[i].quantity);
    }
}

void add_to_fridge(fridge_t *fridge, char *ingredient, int quantity)
{
    int idx = find_ingredient(fridge, ingredient);
    
    if (idx == -1) {
        printf("'addToFridge %s %d': Invalid operation\n", ingredient, quantity);
        return;
    }
    
    fridge->ingredients[idx].quantity += quantity;
}

int can_make_pizza(fridge_t *fridge)
{
    return (fridge->ingredients[0].quantity >= 5 &&  // tomato
            fridge->ingredients[1].quantity >= 1 &&  // dough
            fridge->ingredients[2].quantity >= 3 &&  // onion
            fridge->ingredients[4].quantity >= 8 &&  // olive
            fridge->ingredients[5].quantity >= 8 &&  // pepper
            fridge->ingredients[6].quantity >= 4 &&  // ham
            fridge->ingredients[7].quantity >= 3);   // cheese
}

int can_make_pasta(fridge_t *fridge)
{
    return (fridge->ingredients[0].quantity >= 5 &&  // tomato
            fridge->ingredients[3].quantity >= 2 &&  // pasta
            fridge->ingredients[4].quantity >= 6 &&  // olive
            fridge->ingredients[7].quantity >= 3 &&  // cheese
            fridge->ingredients[6].quantity >= 4);   // ham
}

void make_pizza(fridge_t *fridge)
{
    if (!can_make_pizza(fridge)) {
        if (fridge->ingredients[0].quantity < 5)
            printf("'make pizza': not enough tomato\n");
        else if (fridge->ingredients[1].quantity < 1)
            printf("'make pizza': not enough dough\n");
        else if (fridge->ingredients[2].quantity < 3)
            printf("'make pizza': not enough onion\n");
        else if (fridge->ingredients[4].quantity < 8)
            printf("'make pizza': not enough olive\n");
        else if (fridge->ingredients[5].quantity < 8)
            printf("'make pizza': not enough pepper\n");
        else if (fridge->ingredients[6].quantity < 4)
            printf("'make pizza': not enough ham\n");
        else if (fridge->ingredients[7].quantity < 3)
            printf("'make pizza': not enough cheese\n");
        return;
    }
    
    fridge->ingredients[0].quantity -= 5;  // tomato
    fridge->ingredients[1].quantity -= 1;  // dough
    fridge->ingredients[2].quantity -= 3;  // onion
    fridge->ingredients[4].quantity -= 8;  // olive
    fridge->ingredients[5].quantity -= 8;  // pepper
    fridge->ingredients[6].quantity -= 4;  // ham
    fridge->ingredients[7].quantity -= 3;  // cheese
}

void make_pasta(fridge_t *fridge)
{
    if (!can_make_pasta(fridge)) {
        if (fridge->ingredients[0].quantity < 5)
            printf("'make pasta': not enough tomato\n");
        else if (fridge->ingredients[3].quantity < 2)
            printf("'make pasta': not enough pasta\n");
        else if (fridge->ingredients[4].quantity < 6)
            printf("'make pasta': not enough olive\n");
        else if (fridge->ingredients[7].quantity < 3)
            printf("'make pasta': not enough cheese\n");
        else if (fridge->ingredients[6].quantity < 4)
            printf("'make pasta': not enough ham\n");
        return;
    }
    
    fridge->ingredients[0].quantity -= 5;  // tomato
    fridge->ingredients[3].quantity -= 2;  // pasta
    fridge->ingredients[4].quantity -= 6;  // olive
    fridge->ingredients[7].quantity -= 3;  // cheese
    fridge->ingredients[6].quantity -= 4;  // ham
}

void process_command(fridge_t *fridge, char *line)
{
    char arg1[100];
    int quantity;
    
    if (strncmp(line, "disp fridge", 11) == 0) {
        disp_fridge(fridge);
    } else if (sscanf(line, "addToFridge %s %d", arg1, &quantity) == 2) {
        add_to_fridge(fridge, arg1, quantity);
    } else if (strncmp(line, "make pizza", 10) == 0) {
        make_pizza(fridge);
    } else if (strncmp(line, "make pasta", 10) == 0) {
        make_pasta(fridge);
    } else if (sscanf(line, "make %s", arg1) == 1) {
        printf("'%s': meal unknown\n", arg1);
    } else if (strncmp(line, "exit", 4) == 0) {
        save_fridge(fridge);
        exit(0);
    } else {
        // Remove newline if present
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        printf("'%s': Invalid operation\n", line);
    }
}

int main(void)
{
    fridge_t fridge;
    char line[MAX_LINE];
    
    load_fridge(&fridge);
    
    while (fgets(line, sizeof(line), stdin)) {
        // Remove newline
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        
        process_command(&fridge, line);
    }
    
    save_fridge(&fridge);
    return 0;
}