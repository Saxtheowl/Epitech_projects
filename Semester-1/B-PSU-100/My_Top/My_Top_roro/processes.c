#include "my_top.h"

static char *get_username_by_uid(uid_t uid)
{
    struct passwd *pw;
    
    pw = getpwuid(uid);
    if (pw)
        return my_strdup(pw->pw_name);
    return my_strdup("unknown");
}

static process_t *create_process(int pid)
{
    process_t *proc;
    char path[256];
    char line[1024];
    FILE *file;
    struct stat st;
    
    proc = malloc(sizeof(process_t));
    if (!proc)
        return NULL;
    
    memset(proc, 0, sizeof(process_t));
    proc->pid = pid;
    proc->next = NULL;
    
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    file = fopen(path, "r");
    if (!file) {
        free(proc);
        return NULL;
    }
    
    if (fgets(line, sizeof(line), file)) {
        unsigned long utime, stime;
        sscanf(line, "%d %s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %d %d",
               &proc->pid, proc->command, &proc->state, &utime, &stime, &proc->priority, &proc->nice);
        proc->time = utime + stime;
    }
    fclose(file);
    
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    file = fopen(path, "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "VmSize:", 7) == 0) {
                sscanf(line, "VmSize: %lu", &proc->virt);
            } else if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line, "VmRSS: %lu", &proc->res);
            }
        }
        fclose(file);
    }
    
    snprintf(path, sizeof(path), "/proc/%d", pid);
    if (stat(path, &st) == 0) {
        char *username = get_username_by_uid(st.st_uid);
        if (username) {
            strncpy(proc->user, username, sizeof(proc->user) - 1);
            free(username);
        }
    }
    
    proc->cpu_percent = 0.0;
    proc->mem_percent = 0.0;
    proc->shr = 0;
    
    return proc;
}

process_t *get_processes(char *username_filter)
{
    DIR *proc_dir;
    struct dirent *entry;
    process_t *list = NULL;
    process_t *proc;
    int pid;
    
    proc_dir = opendir(PROC_DIR);
    if (!proc_dir)
        return NULL;
    
    while ((entry = readdir(proc_dir)) != NULL) {
        pid = my_atoi(entry->d_name);
        if (pid <= 0)
            continue;
        
        proc = create_process(pid);
        if (!proc)
            continue;
        
        if (username_filter && my_strcmp(proc->user, username_filter) != 0) {
            free(proc);
            continue;
        }
        
        proc->next = list;
        list = proc;
    }
    
    closedir(proc_dir);
    return list;
}

void free_processes(process_t *list)
{
    process_t *current;
    process_t *next;
    
    current = list;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}