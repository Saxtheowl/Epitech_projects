##
## EPITECH PROJECT, 2024
## Day12 - grep Makefile
## File description:
## Makefile for grep implementation
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = my_grep.c

OBJ = $(SRC:.c=.o)

NAME = grep

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	@echo "Running grep tests..."
	@$(MAKE) -C ../tests tests_run_grep

.PHONY: all clean fclean re tests_run