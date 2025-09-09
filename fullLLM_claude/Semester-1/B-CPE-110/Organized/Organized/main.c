#include "organized.h"

static void free_workshop(workshop_t *workshop)
{
    material_t *current, *next;
    
    if (!workshop)
        return;
    
    current = workshop->materials;
    while (current) {
        next = current->next;
        free_material(current);
        current = next;
    }
    
    free(workshop);
}

int main(void)
{
    workshop_t *workshop = malloc(sizeof(workshop_t));
    int result;
    
    if (!workshop)
        return 84;
    
    workshop->materials = 0;
    workshop->next_id = 0;
    
    result = workshop_shell(workshop);
    
    free_workshop(workshop);
    
    return result;
}