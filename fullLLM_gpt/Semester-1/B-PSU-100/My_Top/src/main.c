#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../include/my_top.h"

static unsigned long long mem_total_kb(void)
{
    FILE *f=fopen("/proc/meminfo","r"); if(!f) return 0; char k[64]; unsigned long long v=0;
    while (fscanf(f, "%63s %llu kB", k, &v)==2){ if (strcmp(k,"MemTotal:")==0) { fclose(f); return v; } }
    fclose(f); return 0;
}

int main(int ac, char **av)
{
    int limit = 10; // default top N
    int batch = 1;  // placeholder, one-shot
    for (int i=1;i<ac;i++){
        if (strcmp(av[i],"-n")==0 && i+1<ac) { limit=atoi(av[++i]); }
        else if (strcmp(av[i],"-i")==0 && i+1<ac) { (void)atoi(av[++i]); /* ignore interval for now */ }
        else if (strcmp(av[i],"-b")==0) { (void)batch; }
        else if (strcmp(av[i],"-h")==0) { printf("Usage: %s [-n N] [-b]\n", av[0]); return 0; }
    }
    proc_t *a=NULL, *b=NULL; int na=0, nb=0;
    cpu_stat_t ca, cb; read_cpu_stat(&ca);
    if (read_processes(&a,&na)!=0) return 84;
    usleep(100000);
    read_cpu_stat(&cb);
    if (read_processes(&b,&nb)!=0) { free(a); return 84; }
    double total = (cb.user-ca.user)+(cb.nice-ca.nice)+(cb.system-ca.system)+(cb.idle-ca.idle)+(cb.iowait-ca.iowait)+(cb.irq-ca.irq)+(cb.softirq-ca.softirq)+(cb.steal-ca.steal);
    unsigned long long mtot = mem_total_kb();
    print_header();
    int shown=0;
    for (int i=0; i<nb && shown<limit; ++i){
        // match pid in snapshot a
        const proc_t *pa=NULL; for (int j=0;j<na;j++){ if (a[j].pid==b[i].pid){ pa=&a[j]; break; } }
        double pcpu = proc_cpu_percent(pa, &b[i], total);
        double pmem = proc_mem_percent(&b[i], mtot);
        print_proc(&b[i], pcpu, pmem); shown++;
    }
    free(a); free(b);
    return 0;
}
