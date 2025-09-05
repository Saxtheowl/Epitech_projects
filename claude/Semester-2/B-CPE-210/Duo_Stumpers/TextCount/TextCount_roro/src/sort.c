/*
** EPITECH PROJECT, 2025
** TextCount
** File description:
** sort
*/

#include "text_count.h"

void sort_by_count(char_count_t *counts, int count_size)
{
    char_count_t temp;
    int i = 0;
    int j = 0;

    for (i = 0; i < count_size - 1; i++) {
        for (j = 0; j < count_size - 1 - i; j++) {
            if (counts[j].count < counts[j + 1].count ||
                (counts[j].count == counts[j + 1].count &&
                counts[j].first_appearance > counts[j + 1].first_appearance)) {
                temp = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = temp;
            }
        }
    }
}

void sort_by_appearance(char_count_t *counts, int count_size)
{
    char_count_t temp;
    int i = 0;
    int j = 0;

    for (i = 0; i < count_size - 1; i++) {
        for (j = 0; j < count_size - 1 - i; j++) {
            if ((counts[j].first_appearance > counts[j + 1].first_appearance &&
                counts[j + 1].first_appearance != 1000) ||
                (counts[j].first_appearance == 1000 &&
                counts[j + 1].first_appearance != 1000)) {
                temp = counts[j];
                counts[j] = counts[j + 1];
                counts[j + 1] = temp;
            }
        }
    }
}