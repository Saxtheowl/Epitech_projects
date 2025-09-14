##
## EPITECH PROJECT, 2024
## Tetris
## File description:
## Makefile for Tetris project
##

NAME = tetris

SRC = main.c \
      args.c \
      tetriminos.c \
      game.c \
      display.c \
      loop.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) -lncurses

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re