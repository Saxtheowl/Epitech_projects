/*
** EPITECH PROJECT, 2025
** My_Top_roro
** File description:
** Prototypes for my_top
*/

#ifndef TOP_H
    #define TOP_H

    #include <stddef.h>

    #define ERR_CODE 84

    typedef struct meminfo_s {
        long mem_total_kb;
        long mem_free_kb;
        long mem_available_kb;
        long buffers_kb;
        long cached_kb;
    } meminfo_t;

    int read_meminfo(meminfo_t *out);
    int count_processes(void);

#endif /* TOP_H */
