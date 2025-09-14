##
## EPITECH PROJECT, 2024
## Minishell1
## File description:
## Makefile for mysh
##

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
NAME    = mysh

SRC     = main.c \
          parser.c \
          executor.c \
          builtins.c \
          env.c \
          path.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re