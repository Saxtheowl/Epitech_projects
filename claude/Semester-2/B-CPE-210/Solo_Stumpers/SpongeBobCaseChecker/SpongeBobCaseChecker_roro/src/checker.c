/*
** EPITECH PROJECT, 2025
** SpongeBobCaseChecker
** File description:
** Main logic for spongebob_case_checker
*/

#include "spongebob_case_checker.h"

int check_spongebob_case(char *str)
{
    int i = 0, consecutive_count = 0, last_was_upper = -1;

    if (!str) {
        print_ok();
        return 0;
    }
    while (str[i]) {
        if (is_letter(str[i])) {
            int current_is_upper = is_upper(str[i]);
            if (last_was_upper == current_is_upper) {
                consecutive_count++;
                if (consecutive_count >= 3) {
                    print_invalid();
                    return 0;
                }
            } else {
                consecutive_count = 0;
                last_was_upper = current_is_upper;
            }
        }
        i++;
    }
    print_ok();
    return 0;
}