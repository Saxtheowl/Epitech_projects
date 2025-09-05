/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Main function for spongebob_case_checker
*/

#include "spongebob_case_checker.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    return check_spongebob_case(argv[1]);
}