##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for Push Swap project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
            src/utils.c \
            src/list_operations.c \
            src/game_operations.c \
            src/rotate_operations.c \
            src/game_management.c \
            src/algorithms.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = push_swap

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	@echo "Testing with already sorted list:"
	./$(NAME) 73 79 83 89 97
	@echo "Testing with single element:"
	./$(NAME) 1789
	@echo "Testing with small list:"
	./$(NAME) 2 1 3 6 5 8

.PHONY: all clean fclean re tests_run