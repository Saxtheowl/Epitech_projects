##
## EPITECH PROJECT, 2024
## My_navy
## File description:
## Makefile for battleship game using Unix signals
##

NAME	= my_navy

SRC	= main.c \
	  utils.c \
	  parser.c \
	  display.c \
	  signals.c \
	  game.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re