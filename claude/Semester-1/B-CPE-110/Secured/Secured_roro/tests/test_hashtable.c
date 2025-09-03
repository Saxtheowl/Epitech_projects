/*
** EPITECH PROJECT, 2025
** Secured
** File description:
** Basic test for hashtable library
*/

#include "hashtable.h"
#include <stdio.h>

int main(void)
{
    hashtable_t *ht = new_hashtable(&hash, 4);
    
    printf("=== HASHTABLE TEST ===\n");
    printf("Creating hashtable with size 4...\n");
    ht_dump(ht);
    
    printf("\nInserting values...\n");
    ht_insert(ht, "Vision", "./Documents/Tournament/Modules/Vision");
    ht_insert(ht, "Kratos", "./Trash/Hollidays_Pics/.secret_folder/kratos.ai");
    ht_insert(ht, "<3", "+33 6 31 45 61 23 71");
    ht_dump(ht);
    
    printf("\nSearching for 'Kratos':\n");
    char *result = ht_search(ht, "Kratos");
    if (result)
        printf("Found: %s\n", result);
    else
        printf("Not found\n");
    
    printf("\nDeleting 'Vision'...\n");
    ht_delete(ht, "Vision");
    ht_dump(ht);
    
    printf("\nTesting collision with '</3'...\n");
    ht_insert(ht, "</3", "+33 7 51 49 01 38 11");
    ht_dump(ht);
    
    delete_hashtable(ht);
    printf("\nHashtable destroyed successfully!\n");
    
    return 0;
}