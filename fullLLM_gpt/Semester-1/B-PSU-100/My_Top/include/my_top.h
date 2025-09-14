#ifndef MY_TOP_H
#define MY_TOP_H

#include <sys/types.h>

typedef struct {
    int pid;
    char user[32];
    char state;
    unsigned long utime, stime;
    unsigned long vsize; // bytes
    long rss;            // pages
    char cmd[256];
} proc_t;

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} cpu_stat_t;

int read_processes(proc_t **out, int *n);
int read_cpu_stat(cpu_stat_t *s);
double cpu_usage(const cpu_stat_t *a, const cpu_stat_t *b);
double proc_cpu_percent(const proc_t *a, const proc_t *b, double total_jiffies);
double proc_mem_percent(const proc_t *p, unsigned long long mem_total_kb);
void print_header(void);
void print_proc(const proc_t *p, double pcpu, double pmem);

#endif

