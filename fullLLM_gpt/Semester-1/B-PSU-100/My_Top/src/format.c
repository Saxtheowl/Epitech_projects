#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>
#include "../include/my_top.h"

void print_header(void)
{
    printf("%5s %-8s %1s %6s %6s %6s %5s %5s %7s  %s\n",
           "PID", "USER", "S", "%CPU", "%MEM", "VSZ", "RSS", "UTIME", "STIME", "COMMAND");
}

void print_proc(const proc_t *p, double pcpu, double pmem)
{
    printf("%5d %-8.8s %c %6.2f %6.2f %6lu %5ld %5lu %6lu  %.50s\n",
           p->pid, p->user, p->state, pcpu, pmem,
           (unsigned long)(p->vsize/1024), (long)p->rss,
           (unsigned long)p->utime, (unsigned long)p->stime, p->cmd);
}

