##
## EPITECH PROJECT, 2024
## Dante's Star - Solver
## File description:
## Makefile for maze solver
##

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include
NAME = solver

SRC = solver.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re