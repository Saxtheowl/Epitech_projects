/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Sudoers file parsing and permission checking
*/

#include "my_sudo.h"

static sudoers_entry_t *create_entry(const char *identifier)
{
    sudoers_entry_t *entry = malloc(sizeof(sudoers_entry_t));
    
    if (!entry)
        return NULL;
    
    entry->user_or_group = strdup(identifier);
    entry->is_group = 0;
    entry->is_uid = 0;
    entry->is_gid = 0;
    entry->uid = (uid_t)-1;
    entry->gid = (gid_t)-1;
    entry->next = NULL;
    
    if (identifier[0] == '%') {
        entry->is_group = 1;
        if (identifier[1] == '#') {
            entry->is_gid = 1;
            entry->gid = atoi(identifier + 2);
        }
    } else if (identifier[0] == '#') {
        entry->is_uid = 1;
        entry->uid = atoi(identifier + 1);
    }
    
    return entry;
}

static int parse_sudoers_line(const char *line, sudoers_entry_t **entries)
{
    char *line_copy = strdup(line);
    char *token = NULL;
    char *saveptr = NULL;
    sudoers_entry_t *entry = NULL;
    sudoers_entry_t *current = *entries;
    
    if (!line_copy)
        return -1;
    
    token = strtok_r(line_copy, " \t", &saveptr);
    if (!token || token[0] == '#') {
        free(line_copy);
        return 0;
    }
    
    entry = create_entry(token);
    if (!entry) {
        free(line_copy);
        return -1;
    }
    
    if (!*entries) {
        *entries = entry;
    } else {
        while (current->next)
            current = current->next;
        current->next = entry;
    }
    
    free(line_copy);
    return 0;
}

int read_sudoers(sudoers_entry_t **entries)
{
    FILE *file = fopen("/etc/sudoers", "r");
    char line[MAX_LINE_LEN];
    
    if (!file) {
        perror("my_sudo: /etc/sudoers");
        return -1;
    }
    
    *entries = NULL;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (parse_sudoers_line(line, entries) != 0) {
            fclose(file);
            return -1;
        }
    }
    
    fclose(file);
    return 0;
}

int is_user_in_group(const char *username, const char *groupname)
{
    struct group *grp = getgrnam(groupname);
    int i = 0;
    
    if (!grp)
        return 0;
    
    while (grp->gr_mem[i]) {
        if (strcmp(grp->gr_mem[i], username) == 0)
            return 1;
        i++;
    }
    
    struct passwd *pwd = getpwnam(username);
    if (pwd && pwd->pw_gid == grp->gr_gid)
        return 1;
    
    return 0;
}

static int check_entry_match(const char *username, sudoers_entry_t *entry)
{
    struct passwd *pwd = getpwnam(username);
    
    if (!pwd)
        return 0;
    
    if (entry->is_uid) {
        return (pwd->pw_uid == entry->uid);
    } else if (entry->is_gid) {
        return (pwd->pw_gid == entry->gid);
    } else if (entry->is_group) {
        return is_user_in_group(username, entry->user_or_group + 1);
    } else {
        return (strcmp(username, entry->user_or_group) == 0);
    }
}

int check_permissions(const char *username, sudoers_entry_t *entries)
{
    sudoers_entry_t *current = entries;
    
    while (current) {
        if (check_entry_match(username, current))
            return 0;
        current = current->next;
    }
    
    return -1;
}

void cleanup_sudoers(sudoers_entry_t *entries)
{
    sudoers_entry_t *current = entries;
    sudoers_entry_t *next = NULL;
    
    while (current) {
        next = current->next;
        free(current->user_or_group);
        free(current);
        current = next;
    }
}