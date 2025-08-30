##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for star project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = star.c
OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = star

all: $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	rm -f tests/*.o

fclean: clean
	rm -f $(NAME) test_star

re: fclean all

test: all
	$(CC) $(CFLAGS) -o test_star tests/test_main.c star.c \
		lib/my/my_putchar.c
	./test_star 1

tests_run:
	$(CC) $(CFLAGS) -o tests_run tests/test_star.c star.c \
		lib/my/my_putchar.c -lcriterion --coverage
	./tests_run

.PHONY: all clean fclean re test tests_run