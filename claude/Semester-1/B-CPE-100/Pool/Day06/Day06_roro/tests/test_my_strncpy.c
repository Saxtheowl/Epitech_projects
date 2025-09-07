#include <criterion/criterion.h>
#include <string.h>

char *my_strncpy(char *dest, char const *src, int n);

Test(my_strncpy, copy_five_characters_in_empty_array)
{
    char dest[6] = {0};
    my_strncpy(dest, "HelloWorld", 5);
    cr_assert_str_eq(dest, "Hello");
}

Test(my_strncpy, copy_string_in_empty_array)
{
    char my_dest[6] = {0};
    char dest[6] = {0};
    my_strncpy(my_dest, "Hello", 6);
    strncpy(dest, "Hello", 6);
    cr_assert_str_eq(my_dest, dest);
}

Test(my_strncpy, copy_zero_characters)
{
    char dest[10] = "original";
    my_strncpy(dest, "new", 0);
    cr_assert_str_eq(dest, "original");
}

Test(my_strncpy, copy_more_than_src_length)
{
    char dest[10] = {0};
    my_strncpy(dest, "hi", 5);
    cr_assert_str_eq(dest, "hi");
    cr_assert_eq(dest[2], '\0');
    cr_assert_eq(dest[3], '\0');
    cr_assert_eq(dest[4], '\0');
}