/*
** EPITECH PROJECT, 2024
** Pokemon
** File description:
** Pokemon battle simulator
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

#define MAX_POKEMON 1000
#define MAX_NAME_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    int attack;
    int defense;
    int speed;
    int health;
    int max_health;
} pokemon_t;

typedef struct {
    pokemon_t *pokemon;
    int count;
} pokedex_t;

void print_usage(void)
{
    fprintf(stderr, "Usage: ./pokemon [pokemon1] [pokemon2]\n");
}

int my_strcmp_case_insensitive(char *s1, char *s2)
{
    int i = 0;
    char c1, c2;
    
    while (s1[i] && s2[i]) {
        c1 = s1[i];
        c2 = s2[i];
        
        if (c1 >= 'A' && c1 <= 'Z')
            c1 = c1 - 'A' + 'a';
        if (c2 >= 'A' && c2 <= 'Z')
            c2 = c2 - 'A' + 'a';
            
        if (c1 != c2)
            return c1 - c2;
        i++;
    }
    
    return s1[i] - s2[i];
}

int parse_pokemon_line(char *line, pokemon_t *pokemon)
{
    char *token;
    char *line_copy = malloc(strlen(line) + 1);
    int field = 0;
    
    if (!line_copy)
        return 0;
    
    strcpy(line_copy, line);
    
    token = strtok(line_copy, ";");
    while (token && field < 5) {
        switch (field) {
            case 0:
                if (strlen(token) >= MAX_NAME_LEN) {
                    free(line_copy);
                    return 0;
                }
                strcpy(pokemon->name, token);
                break;
            case 1:
                pokemon->attack = atoi(token);
                if (pokemon->attack < 0) {
                    free(line_copy);
                    return 0;
                }
                break;
            case 2:
                pokemon->defense = atoi(token);
                if (pokemon->defense < 0) {
                    free(line_copy);
                    return 0;
                }
                break;
            case 3:
                pokemon->speed = atoi(token);
                if (pokemon->speed < 0) {
                    free(line_copy);
                    return 0;
                }
                break;
            case 4:
                pokemon->health = atoi(token);
                pokemon->max_health = pokemon->health;
                if (pokemon->health <= 0) {
                    free(line_copy);
                    return 0;
                }
                break;
        }
        field++;
        token = strtok(NULL, ";");
    }
    
    free(line_copy);
    return (field == 5);
}

int load_pokemon_file(char *filepath, pokedex_t *pokedex)
{
    FILE *file = fopen(filepath, "r");
    char buffer[512];
    pokemon_t temp_pokemon;
    
    if (!file)
        return 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        // Remove newline
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        
        // Skip comments and empty lines
        if (buffer[0] == '#' || strlen(buffer) == 0)
            continue;
        
        if (parse_pokemon_line(buffer, &temp_pokemon)) {
            if (pokedex->count < MAX_POKEMON) {
                pokedex->pokemon[pokedex->count] = temp_pokemon;
                pokedex->count++;
            }
        }
    }
    
    fclose(file);
    return 1;
}

int load_all_pokemon(pokedex_t *pokedex)
{
    DIR *dir = opendir("pokecfg");
    struct dirent *entry;
    char filepath[512];
    
    if (!dir) {
        fprintf(stderr, "Error: Cannot open pokecfg directory\n");
        return 84;
    }
    
    pokedex->pokemon = malloc(sizeof(pokemon_t) * MAX_POKEMON);
    if (!pokedex->pokemon) {
        closedir(dir);
        return 84;
    }
    
    pokedex->count = 0;
    
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
            
        snprintf(filepath, sizeof(filepath), "pokecfg/%s", entry->d_name);
        load_pokemon_file(filepath, pokedex);
    }
    
    closedir(dir);
    return 0;
}

void sort_pokemon(pokedex_t *pokedex)
{
    int i, j;
    pokemon_t temp;
    
    for (i = 0; i < pokedex->count - 1; i++) {
        for (j = 0; j < pokedex->count - i - 1; j++) {
            if (my_strcmp_case_insensitive(pokedex->pokemon[j].name, 
                                         pokedex->pokemon[j + 1].name) > 0) {
                temp = pokedex->pokemon[j];
                pokedex->pokemon[j] = pokedex->pokemon[j + 1];
                pokedex->pokemon[j + 1] = temp;
            }
        }
    }
}

void print_all_pokemon(pokedex_t *pokedex)
{
    int i;
    
    for (i = 0; i < pokedex->count; i++) {
        printf("Pokemon %s has %d attack, %d defense, %d speed and %d health.\n",
               pokedex->pokemon[i].name,
               pokedex->pokemon[i].attack,
               pokedex->pokemon[i].defense,
               pokedex->pokemon[i].speed,
               pokedex->pokemon[i].health);
    }
}

pokemon_t *find_pokemon(pokedex_t *pokedex, char *name)
{
    int i;
    
    for (i = 0; i < pokedex->count; i++) {
        if (strcmp(pokedex->pokemon[i].name, name) == 0) {
            return &pokedex->pokemon[i];
        }
    }
    
    return NULL;
}

void simulate_battle(pokemon_t *p1, pokemon_t *p2)
{
    pokemon_t *attacker, *defender, *temp;
    int damage, blocked, final_damage;
    
    // Reset health
    p1->health = p1->max_health;
    p2->health = p2->max_health;
    
    // Determine who starts (highest speed)
    if (p1->speed >= p2->speed) {
        attacker = p1;
        defender = p2;
    } else {
        attacker = p2;
        defender = p1;
    }
    
    srand(time(NULL));
    
    while (p1->health > 0 && p2->health > 0) {
        // Calculate damage (random between 0 and attack)
        damage = rand() % (attacker->attack + 1);
        blocked = defender->defense;
        final_damage = damage - blocked;
        
        if (final_damage < 0)
            final_damage = 0;
        
        printf("%s attacks for %d damage\n", attacker->name, damage);
        printf("%s blocks %d damage\n", defender->name, blocked);
        
        defender->health -= final_damage;
        if (defender->health < 0)
            defender->health = 0;
            
        printf("%s loses %d health (%d left)\n", 
               defender->name, final_damage, defender->health);
        
        if (defender->health == 0) {
            printf("%s is KO\n", defender->name);
            printf("%s wins the fight!\n", attacker->name);
            break;
        }
        
        // Switch attacker and defender
        temp = attacker;
        attacker = defender;
        defender = temp;
    }
}

int main(int argc, char **argv)
{
    pokedex_t pokedex;
    pokemon_t *p1, *p2;
    
    if (load_all_pokemon(&pokedex) != 0)
        return 84;
    
    if (pokedex.count == 0) {
        fprintf(stderr, "Error: No Pokemon found\n");
        free(pokedex.pokemon);
        return 84;
    }
    
    sort_pokemon(&pokedex);
    print_all_pokemon(&pokedex);
    
    if (argc != 3) {
        free(pokedex.pokemon);
        return 0;
    }
    
    p1 = find_pokemon(&pokedex, argv[1]);
    p2 = find_pokemon(&pokedex, argv[2]);
    
    if (!p1) {
        fprintf(stderr, "Error: Pokemon %s not found\n", argv[1]);
        free(pokedex.pokemon);
        return 84;
    }
    
    if (!p2) {
        fprintf(stderr, "Error: Pokemon %s not found\n", argv[2]);
        free(pokedex.pokemon);
        return 84;
    }
    
    simulate_battle(p1, p2);
    
    free(pokedex.pokemon);
    return 0;
}