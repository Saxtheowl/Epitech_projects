##
## EPITECH PROJECT, 2024
## MyWorld
## File description:
## Makefile for MyWorld terrain editor
##

NAME	=	my_world

SRC	=	src/main.c		\
	src/core.c		\
	src/map.c		\
	src/ui.c		\
	src/camera.c		\
	src/events.c		\
	src/render.c		\
	src/tools.c		\
	src/utils.c		\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c99 -I./include

LDFLAGS	=	-lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re