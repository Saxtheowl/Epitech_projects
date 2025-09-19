/*
** EPITECH PROJECT, 2025
** My_sudo
** File description:
** Sudoers file parsing for my_sudo
*/

#include "my_sudo.h"

int check_user_in_group(const char *username, const char *groupname)
{
    struct group *grp;
    char **members;

    grp = getgrnam(groupname);
    if (!grp)
        return 0;

    // Check if user's primary group matches
    struct passwd *pw = getpwnam(username);
    if (pw && pw->pw_gid == grp->gr_gid)
        return 1;

    // Check if user is in group members list
    members = grp->gr_mem;
    while (members && *members) {
        if (strcmp(*members, username) == 0)
            return 1;
        members++;
    }

    return 0;
}

int check_user_by_uid(const char *username, uid_t uid)
{
    struct passwd *pw = getpwnam(username);
    return (pw && pw->pw_uid == uid);
}

int check_group_by_gid(const char *username, gid_t gid)
{
    struct passwd *pw = getpwnam(username);
    if (!pw)
        return 0;

    // Check primary group
    if (pw->pw_gid == gid)
        return 1;

    // Check supplementary groups
    gid_t *groups;
    int ngroups = 0;

    getgrouplist(pw->pw_name, pw->pw_gid, NULL, &ngroups);
    groups = malloc(ngroups * sizeof(gid_t));

    if (getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups) != -1) {
        for (int i = 0; i < ngroups; i++) {
            if (groups[i] == gid) {
                free(groups);
                return 1;
            }
        }
    }

    free(groups);
    return 0;
}

int check_sudoers_permission(const char *username)
{
    FILE *sudoers_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int allowed = 0;

    sudoers_file = fopen("/etc/sudoers", "r");
    if (!sudoers_file) {
        // If can't read sudoers, try a simple check
        // For testing purposes, allow users in wheel or sudo group
        return check_user_in_group(username, "wheel") ||
               check_user_in_group(username, "sudo");
    }

    while ((read = getline(&line, &len, sudoers_file)) != -1) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
            continue;

        // Check for direct user match
        if (strstr(line, username) == line) {
            char *token = strtok(line, " \t");
            if (token && strcmp(token, username) == 0) {
                allowed = 1;
                break;
            }
        }

        // Check for group match (% prefix)
        if (line[0] == '%') {
            char *groupname = line + 1;
            char *space = strchr(groupname, ' ');
            if (space) {
                *space = '\0';
                if (check_user_in_group(username, groupname)) {
                    allowed = 1;
                    break;
                }
            }
        }

        // Check for UID match (# prefix)
        if (line[0] == '#' && line[1] >= '0' && line[1] <= '9') {
            uid_t uid = (uid_t)atoi(line + 1);
            if (check_user_by_uid(username, uid)) {
                allowed = 1;
                break;
            }
        }

        // Check for GID match (%# prefix)
        if (strncmp(line, "%#", 2) == 0) {
            gid_t gid = (gid_t)atoi(line + 2);
            if (check_group_by_gid(username, gid)) {
                allowed = 1;
                break;
            }
        }
    }

    if (line)
        free(line);
    fclose(sudoers_file);

    return allowed;
}