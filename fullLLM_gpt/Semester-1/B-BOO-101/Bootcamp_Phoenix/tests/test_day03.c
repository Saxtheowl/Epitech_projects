#include "framework.h"
#include "phoenix.h"

Test(concat_strings, appends_source)
{
    char buffer[32] = "Hello";

    concat_strings(buffer, " World");
    cr_assert_str_eq(buffer, "Hello World");
}

Test(concat_strings, ignores_null_inputs)
{
    char buffer[8] = "Hi";

    cr_assert_null(concat_strings(NULL, buffer));
    cr_assert_eq(concat_strings(buffer, NULL), buffer);
    cr_assert_str_eq(buffer, "Hi");
}
