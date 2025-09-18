##
## EPITECH PROJECT, 2024
## Minishell1 Bootstrap - Makefile
## File description:
## Makefile for my_exec bootstrap project
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
SRC = $(SRC_DIR)/my_exec.c

OBJ = $(SRC:.c=.o)

NAME = my_exec

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re