##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for fir tree project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/tree.c src/tree_utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = tree

all: $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	rm -f tests/*.o

fclean: clean
	rm -f $(NAME)
	rm -f test_tree

re: fclean all

test: all
	$(CC) $(CFLAGS) -o test_tree tests/test_main.c tree.c
	./test_tree

tests_run:
	$(CC) $(CFLAGS) -o tests_run tests/test_tree.c tree.c \
		-lcriterion --coverage
	./tests_run

.PHONY: all clean fclean re test tests_run