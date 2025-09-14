#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../include/my_top.h"

static int is_digits(const char *s){ for (; *s; ++s) if (*s<'0'||*s>'9') return 0; return 1; }

static int read_cmdline(int pid, char *buf, size_t sz)
{
    char path[64]; snprintf(path, sizeof path, "/proc/%d/cmdline", pid);
    int fd = open(path, O_RDONLY); if (fd<0){ buf[0]='\0'; return -1; }
    ssize_t r = read(fd, buf, sz-1); if (r<0){ close(fd); buf[0]='\0'; return -1; }
    close(fd);
    for (ssize_t i=0;i<r;i++) if (buf[i]=='\0') buf[i]=' ';
    buf[r]='\0'; if (r==0) snprintf(buf, sz, "[%d]", pid);
    return 0;
}

static int read_status_user(int pid, char *user, size_t usz)
{
    char path[64]; snprintf(path, sizeof path, "/proc/%d/status", pid);
    FILE *f=fopen(path, "r"); if(!f){ strncpy(user, "?", usz); return -1; }
    uid_t uid=0; char line[256];
    while (fgets(line, sizeof line, f)){
        if (sscanf(line, "Uid:\t%u", &uid)==1) break;
    }
    fclose(f);
    struct passwd *pw = getpwuid(uid);
    snprintf(user, usz, "%s", pw? pw->pw_name : "?");
    return 0;
}

int read_processes(proc_t **out, int *n)
{
    DIR *d = opendir("/proc"); if(!d) return -1;
    int cap=256, cnt=0; proc_t *arr = malloc(cap*sizeof(*arr)); if(!arr){closedir(d);return -1;}
    struct dirent *de;
    while ((de=readdir(d))){
        if (!is_digits(de->d_name)) continue;
        int pid = atoi(de->d_name);
        char path[64]; snprintf(path, sizeof path, "/proc/%d/stat", pid);
        FILE *f = fopen(path, "r"); if(!f) continue;
        // Fields: pid (1) comm (2) state (3) ... utime(14) stime(15) vsize(23) rss(24)
        proc_t p; memset(&p,0,sizeof p); p.pid=pid;
        fscanf(f, "%d (%255[^)]) %c", &p.pid, p.cmd, &p.state);
        // skip fields 4..13
        unsigned long skip; for (int i=0;i<10;i++) fscanf(f, "%lu", &skip);
        fscanf(f, "%lu %lu", &p.utime, &p.stime);
        // skip fields 16..22
        for (int i=0;i<7;i++) fscanf(f, "%lu", &skip);
        fscanf(f, "%lu %ld", &p.vsize, &p.rss);
        fclose(f);
        if (p.cmd[0]=='\0') read_cmdline(pid, p.cmd, sizeof p.cmd);
        read_status_user(pid, p.user, sizeof p.user);
        if (cnt==cap){ cap*=2; proc_t *na=realloc(arr, cap*sizeof(*na)); if(!na){free(arr);closedir(d);return -1;} arr=na; }
        arr[cnt++]=p;
    }
    closedir(d);
    *out=arr; *n=cnt; return 0;
}

int read_cpu_stat(cpu_stat_t *s)
{
    FILE *f=fopen("/proc/stat","r"); if(!f) return -1; char cpu[5];
    memset(s,0,sizeof *s);
    if (fscanf(f, "%4s %llu %llu %llu %llu %llu %llu %llu %llu", cpu, &s->user,&s->nice,&s->system,&s->idle,&s->iowait,&s->irq,&s->softirq,&s->steal) < 5){ fclose(f); return -1; }
    fclose(f); return 0;
}

double cpu_usage(const cpu_stat_t *a, const cpu_stat_t *b)
{
    unsigned long long idle_a = a->idle + a->iowait;
    unsigned long long idle_b = b->idle + b->iowait;
    unsigned long long non_a = a->user + a->nice + a->system + a->irq + a->softirq + a->steal;
    unsigned long long non_b = b->user + b->nice + b->system + b->irq + b->softirq + b->steal;
    unsigned long long totald = (idle_b+non_b) - (idle_a+non_a);
    unsigned long long idled  = idle_b - idle_a;
    if (totald==0) return 0.0;
    return (double)(totald - idled) * 100.0 / (double)totald;
}

double proc_cpu_percent(const proc_t *a, const proc_t *b, double total_jiffies)
{
    if (!a || !b || b->pid!=a->pid) return 0.0;
    unsigned long du = (b->utime + b->stime) - (a->utime + a->stime);
    if (total_jiffies <= 0.0) return 0.0;
    return (double)du * 100.0 / total_jiffies;
}

double proc_mem_percent(const proc_t *p, unsigned long long mem_total_kb)
{
    long page_kb = sysconf(_SC_PAGESIZE) / 1024;
    unsigned long long rss_kb = (unsigned long long)(p->rss < 0 ? 0 : p->rss) * (unsigned long long)page_kb;
    if (mem_total_kb==0) return 0.0;
    return (double)rss_kb * 100.0 / (double)mem_total_kb;
}
