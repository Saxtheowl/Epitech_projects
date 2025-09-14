##
## EPITECH PROJECT, 2024
## Dante - Solver
## File description:
## Makefile for maze solver
##

NAME = solver

SRC = main.c \
      maze_loader.c \
      maze_solver.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re