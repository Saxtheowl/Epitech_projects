##
## EPITECH PROJECT, 2024
## TicTacToe
## File description:
## Makefile for tictactoe
##

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99
NAME    = tictactoe

SRC     = main.c \
          args.c \
          game.c \
          input.c \
          win_check.c \
          game_loop.c

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