int mini_printf(const char *format, ...);

int main(void)
{
    mini_printf("Test null string: %s\n", (char*)0);
    mini_printf("Test zero: %d\n", 0);
    mini_printf("Test negative: %d\n", -42);
    mini_printf("Test INT_MIN: %d\n", -2147483648);
    mini_printf("Just text without flags\n");
    mini_printf("%%d gives: %d\n", 42);
    
    return 0;
}