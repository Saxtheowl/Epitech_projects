/*
** EPITECH PROJECT, 2025
** TextToMultiTap
** File description:
** Main function for text_to_multi_tap
*/

#include "text_to_multi_tap.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    return text_to_multi_tap(argv[1]);
}