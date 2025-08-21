##
## EPITECH PROJECT, 2024
## MyHunter
## File description:
## Makefile for MyHunter project
##

NAME	= my_hunter

SRC	= src/main.c \
	  src/game_init.c \
	  src/game_loop.c \
	  src/duck_manager.c \
	  src/utils.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -I./include

LDFLAGS	= -lcsfml-graphics -lcsfml-audio -lcsfml-system -lcsfml-window -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f high_score.txt

re: fclean all

.PHONY: all clean fclean re