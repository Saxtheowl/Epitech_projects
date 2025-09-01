##
## EPITECH PROJECT, 2024
## MyRPG
## File description:
## Makefile for MyRPG project
##

NAME	=	my_rpg

SRC	=	src/core.c		\
	src/scenes.c		\
	src/player.c		\
	src/enemies.c		\
	src/combat.c		\
	src/inventory.c		\
	src/quests.c		\
	src/particles.c		\
	src/npcs.c		\
	src/map.c		\
	src/camera.c		\
	src/ui.c		\
	src/save.c		\
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