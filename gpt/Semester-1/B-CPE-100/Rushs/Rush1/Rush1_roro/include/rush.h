/*
** EPITECH PROJECT, 2025
** Rush1_roro
** File description:
** Prototypes for rush1 rectangles
*/

#ifndef RUSH_H
    #define RUSH_H

    #define ERR_CODE 84

    typedef struct pattern_s {
        char tl;
        char tr;
        char bl;
        char br;
        char h;
        char v;
    } pattern_t;

    int draw_rect(int w, int h, pattern_t p);

#endif /* RUSH_H */
