#include "my_ls.h"

file_info_t *create_file_info(char *name, char *path)
{
    file_info_t *info;
    
    info = malloc(sizeof(file_info_t));
    if (!info)
        return NULL;
    
    info->name = my_strdup(name);
    info->path = my_strdup(path);
    info->next = NULL;
    
    if (!info->name || !info->path) {
        if (info->name)
            free(info->name);
        if (info->path)
            free(info->path);
        free(info);
        return NULL;
    }
    
    if (lstat(path, &info->st) == -1) {
        free(info->name);
        free(info->path);
        free(info);
        return NULL;
    }
    
    return info;
}

void free_file_list(file_info_t *list)
{
    file_info_t *current = list;
    file_info_t *next;
    
    while (current) {
        next = current->next;
        if (current->name)
            free(current->name);
        if (current->path)
            free(current->path);
        free(current);
        current = next;
    }
}

file_info_t *add_file_to_list(file_info_t *list, file_info_t *new_file)
{
    if (!new_file)
        return list;
    
    if (!list)
        return new_file;
    
    new_file->next = list;
    return new_file;
}