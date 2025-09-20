CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99 --coverage -I../includes
LDFLAGS = --coverage
LDLIBS  = 
TARGET  = unit_tests
TEST_SRCS = framework.c test_day01.c test_day02.c test_day03.c test_day04.c
CODE_SRCS = \
	../lib/phoenix/my_putchar.c \
	../Day01/show_alphabet.c \
	../Day01/show_combinations.c \
	../Day01/show_number.c \
	../Day01/show_string.c \
	../Day01/reverse_string.c \
	../Day01/to_number.c \
	../Day02/iterative_factorial.c \
	../Day02/recursive_power.c \
	../Day02/is_prime_number.c \
	../Day02/my_strcpy.c \
	../Day02/my_strncmp.c \
	../Day02/my_strstr.c \
	../Day02/my_strupcase.c \
	../Day02/my_strcapitalize.c \
	../Day03/concat_strings.c \
	../Day04/duplicate_string.c \
	../Day04/split_string.c \
	../Day04/show_string_array.c \
	../Day04/parameters_to_array.c \
	../Day04/show_parameters_array.c \
	../Day04/task02/concat_parameters.c

all: $(TARGET)

$(TARGET): $(TEST_SRCS) $(CODE_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o *.gcno *.gcda

fclean: clean

re: fclean all

.PHONY: all test clean fclean re
