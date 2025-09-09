##
## EPITECH PROJECT, 2024
## my_sokoban
## File description:
## Makefile
##

NAME	= my_sokoban

SRC	= main.c \
	  utils.c \
	  map.c \
	  game.c \
	  display.c \
	  game_loop.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re