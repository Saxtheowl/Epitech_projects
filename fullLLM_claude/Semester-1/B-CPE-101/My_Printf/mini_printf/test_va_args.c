#include "includes/bsprintf.h"
#include <stdio.h>

int main(void)
{
    int result;

    // Test sum_numbers according to PDF
    result = sum_numbers(3, 21, 25, -4);
    printf("sum_numbers(3, 21, 25, -4) = %d (expected: 42)\n", result);

    // Test sum_strings_length according to PDF
    result = sum_strings_length(5, "Hello", "a", "toto", "", "plop");
    printf("sum_strings_length(5, \"Hello\", \"a\", \"toto\", \"\", \"plop\") = %d (expected: 14)\n", result);

    // Test disp_stdarg according to PDF
    printf("disp_stdarg(\"csiis\", 'X', \"hi\", 10, -3, \"plop\"):\n");
    disp_stdarg("csiis", 'X', "hi", 10, -3, "plop");

    return 0;
}