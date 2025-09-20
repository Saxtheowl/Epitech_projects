#include "framework.h"
#include "phoenix.h"
#include <stdlib.h>

static void free_parameters(struct info_param *params)
{
    if (!params) {
        return;
    }
    for (int i = 0; params[i].str != NULL; ++i) {
        free(params[i].copy);
        if (params[i].word_array) {
            for (int j = 0; params[i].word_array[j] != NULL; ++j) {
                free(params[i].word_array[j]);
            }
            free(params[i].word_array);
        }
    }
    free(params);
}

Test(duplicate_string, duplicates_content)
{
    char *copy = duplicate_string("Phoenix");

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "Phoenix");
    free(copy);
}

Test(split_string, splits_on_non_alphanum)
{
    char **array = split_string("Hello, World! 42 times");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "World");
    cr_assert_str_eq(array[2], "42");
    cr_assert_str_eq(array[3], "times");
    cr_assert_null(array[4]);
    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}

Test(split_string, handles_empty_string)
{
    char **array = split_string("");

    cr_assert_not_null(array);
    cr_assert_null(array[0]);
    free(array);
}

Test(parameters_to_array, builds_parameter_list)
{
    char *argv[] = {"./program", "Hello World", NULL};
    struct info_param *params = parameters_to_array(2, argv);

    cr_assert_not_null(params);
    cr_assert_str_eq(params[0].str, "./program");
    cr_assert_eq(params[0].length, 9);
    cr_assert_str_eq(params[0].copy, "./program");
    cr_assert_str_eq(params[1].word_array[0], "Hello");
    cr_assert_str_eq(params[1].word_array[1], "World");
    cr_assert_null(params[2].str);
    free_parameters(params);
}

Test(show_string_array, prints_each_word)
{
    char *words[] = {"One", "Two", NULL};

    cr_redirect_stdout();
    show_string_array(words);
    cr_assert_stdout_eq_str("One\nTwo\n");
}

Test(show_parameters_array, prints_structure)
{
    char *argv[] = {"./app", "Hello", NULL};
    struct info_param *params = parameters_to_array(2, argv);

    cr_redirect_stdout();
    show_parameters_array(params);
    cr_assert_stdout_eq_str("./app\n5\napp\nHello\n5\nHello\n");
    free_parameters(params);
}
