##
## EPITECH PROJECT, 2024
## Dante's Star - Generator
## File description:
## Makefile for maze generator
##

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include
NAME = generator

SRC = generator.c
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