/*
** EPITECH PROJECT, 2025
** My_Top_roro
** File description:
** /proc helpers
*/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "top.h"

static long parse_kb(const char *line)
{
    const char *p;
    long v;

    p = line;
    while (*p && (*p < '0' || *p > '9'))
        p += 1;
    v = 0;
    while (*p >= '0' && *p <= '9') {
        v = v * 10 + (*p - '0');
        p += 1;
    }
    return v;
}

int read_meminfo(meminfo_t *out)
{
    FILE *fp;
    char line[256];

    fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return -1;
    out->mem_total_kb = 0;
    out->mem_free_kb = 0;
    out->mem_available_kb = 0;
    out->buffers_kb = 0;
    out->cached_kb = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strncmp(line, "MemTotal:", 9) == 0)
            out->mem_total_kb = parse_kb(line);
        else if (strncmp(line, "MemFree:", 8) == 0)
            out->mem_free_kb = parse_kb(line);
        else if (strncmp(line, "MemAvailable:", 13) == 0)
            out->mem_available_kb = parse_kb(line);
        else if (strncmp(line, "Buffers:", 8) == 0)
            out->buffers_kb = parse_kb(line);
        else if (strncmp(line, "Cached:", 7) == 0)
            out->cached_kb = parse_kb(line);
    }
    fclose(fp);
    return 0;
}

int count_processes(void)
{
    DIR *d;
    struct dirent *de;
    int count;
    int i;

    d = opendir("/proc");
    if (!d)
        return -1;
    count = 0;
    while ((de = readdir(d)) != NULL) {
        const char *s = de->d_name;
        if (!isdigit((unsigned char)s[0]))
            continue;
        for (i = 1; s[i]; ++i) {
            if (!isdigit((unsigned char)s[i])) { s = NULL; break; }
        }
        if (s)
            count += 1;
    }
    closedir(d);
    return count;
}
