#include "phoenix.h"

int show_parameters_array(struct info_param const *par)
{
    if (!par) {
        return 0;
    }
    for (int i = 0; par[i].str != NULL; ++i) {
        show_string(par[i].str);
        my_putchar('\n');
        show_number(par[i].length);
        my_putchar('\n');
        if (par[i].word_array) {
            for (int j = 0; par[i].word_array[j] != NULL; ++j) {
                show_string(par[i].word_array[j]);
                my_putchar('\n');
            }
        }
    }
    return 0;
}
