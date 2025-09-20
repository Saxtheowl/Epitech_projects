#include "framework.h"
#include "phoenix.h"

static char *generate_combinations(void)
{
    static char buffer[1024];
    int index = 0;

    for (char a = '0'; a <= '7'; ++a) {
        for (char b = a + 1; b <= '8'; ++b) {
            for (char c = b + 1; c <= '9'; ++c) {
                buffer[index++] = a;
                buffer[index++] = b;
                buffer[index++] = c;
                if (!(a == '7' && b == '8' && c == '9')) {
                    buffer[index++] = ',';
                    buffer[index++] = ' ';
                }
            }
        }
    }
    buffer[index++] = '\n';
    buffer[index] = '\0';
    return buffer;
}

Test(show_alphabet, prints_lowercase)
{
    cr_redirect_stdout();
    show_alphabet();
    cr_assert_stdout_eq_str("abcdefghijklmnopqrstuvwxyz\n");
}

Test(show_combinations, prints_all_triples)
{
    cr_redirect_stdout();
    show_combinations();
    cr_assert_stdout_eq_str(generate_combinations());
}

Test(show_number, prints_negative_value)
{
    cr_redirect_stdout();
    show_number(-2147483648);
    cr_assert_stdout_eq_str("-2147483648");
}

Test(show_string, handles_null_pointer)
{
    cr_redirect_stdout();
    show_string(NULL);
    cr_assert_stdout_eq_str("");
}

Test(reverse_string, reverses_even_length)
{
    char buffer[] = "abcdef";

    cr_assert_str_eq(reverse_string(buffer), "fedcba");
}

Test(reverse_string, returns_null_on_null)
{
    cr_assert_null(reverse_string(NULL));
}

Test(to_number, parses_with_multiple_signs)
{
    cr_assert_eq(to_number("+---+--++---+---+---+-42"), -42);
}

Test(to_number, stops_on_non_digit)
{
    cr_assert_eq(to_number("42 a43"), 42);
}

Test(to_number, detects_overflow)
{
    cr_assert_eq(to_number("2147483648"), 0);
    cr_assert_eq(to_number("-2147483649"), 0);
}
