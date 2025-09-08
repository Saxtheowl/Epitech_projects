##
## EPITECH PROJECT, 2024
## Day01 Makefile
## File description:
## Makefile for Day01 tasks
##

CC		= gcc
CFLAGS		= -Wall -Wextra -Werror

SRCDIR		= .
TESTDIR		= tests

SOURCES		= show_alphabet.c show_combinations.c show_number.c \
		  show_string.c reverse_string.c to_number.c

OBJECTS		= $(SOURCES:.c=.o)

all: $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	rm -f test_program

fclean: clean
	rm -f *.o

re: fclean all

test: all
	@mkdir -p $(TESTDIR)
	@echo "Building test program..."
	@$(CC) $(CFLAGS) -o test_program $(TESTDIR)/test_main.c $(SOURCES) $(TESTDIR)/my_putchar.c
	@echo "Running tests..."
	@./test_program
	@echo "All tests completed."

.PHONY: all clean fclean re test