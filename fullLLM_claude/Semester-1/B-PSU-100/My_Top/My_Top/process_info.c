#include "my_top.h"

static int read_process_stat(const char *pid, process_t *proc)
{
    char stat_path[256];
    FILE *fp;
    char comm[256], state;
    int ppid, pgrp, session, tty_nr, tpgid;
    unsigned flags;
    unsigned long minflt, cminflt, majflt, cmajflt, utime, stime;
    long cutime, cstime, priority, nice, num_threads, itrealvalue;
    unsigned long long starttime;
    unsigned long vsize;
    long rss;
    
    snprintf(stat_path, sizeof(stat_path), "%s/%s/stat", PROC_PATH, pid);
    fp = fopen(stat_path, "r");
    if (!fp)
        return -1;
    
    if (fscanf(fp, "%d %255s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld %llu %lu %ld",
               &proc->pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid,
               &flags, &minflt, &cminflt, &majflt, &cmajflt, &utime, &stime,
               &cutime, &cstime, &priority, &nice, &num_threads, &itrealvalue,
               &starttime, &vsize, &rss) != 24) {
        fclose(fp);
        return -1;
    }
    
    proc->priority = (int)priority;
    proc->nice = (int)nice;
    proc->virt = vsize;
    proc->res = rss * getpagesize();
    proc->shr = 0;
    proc->status = state;
    proc->time_total = utime + stime;
    proc->cpu_percent = 0.0;
    proc->mem_percent = 0.0;
    
    if (strlen(comm) > 2 && comm[0] == '(' && comm[strlen(comm)-1] == ')') {
        comm[strlen(comm)-1] = '\0';
        strcpy(proc->command, comm + 1);
    } else {
        strcpy(proc->command, comm);
    }
    
    fclose(fp);
    return 0;
}

static int get_process_user(const char *pid, char *user)
{
    char stat_path[256];
    struct stat st;
    struct passwd *pw;
    
    snprintf(stat_path, sizeof(stat_path), "%s/%s", PROC_PATH, pid);
    if (stat(stat_path, &st) != 0)
        return -1;
    
    pw = getpwuid(st.st_uid);
    if (!pw) {
        snprintf(user, 32, "%d", st.st_uid);
    } else {
        strncpy(user, pw->pw_name, 31);
        user[31] = '\0';
    }
    
    return 0;
}

static int should_include_process(const char *user, const char *filter_user)
{
    if (!filter_user || strlen(filter_user) == 0)
        return 1;
    return strcmp(user, filter_user) == 0;
}

int read_processes(process_t *processes, const char *filter_user)
{
    DIR *proc_dir;
    struct dirent *entry;
    int count = 0;
    char user[32];
    
    proc_dir = opendir(PROC_PATH);
    if (!proc_dir)
        return -1;
    
    while ((entry = readdir(proc_dir)) != NULL && count < MAX_PROCS) {
        if (strspn(entry->d_name, "0123456789") != strlen(entry->d_name))
            continue;
        
        if (read_process_stat(entry->d_name, &processes[count]) != 0)
            continue;
        
        if (get_process_user(entry->d_name, user) != 0)
            continue;
        
        if (!should_include_process(user, filter_user))
            continue;
        
        strcpy(processes[count].user, user);
        count++;
    }
    
    closedir(proc_dir);
    return count;
}

void sort_processes_by_pid(process_t *processes, int count)
{
    int i, j;
    process_t temp;
    
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (processes[j].pid > processes[j + 1].pid) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}