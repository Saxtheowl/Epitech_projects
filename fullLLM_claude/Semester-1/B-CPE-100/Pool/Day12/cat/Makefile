##
## EPITECH PROJECT, 2024
## Day12 - cat Makefile
## File description:
## Makefile for cat implementation
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = my_cat.c

OBJ = $(SRC:.c=.o)

NAME = cat

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	@echo "Running cat tests..."
	@$(MAKE) -C ../tests tests_run_cat

.PHONY: all clean fclean re tests_run