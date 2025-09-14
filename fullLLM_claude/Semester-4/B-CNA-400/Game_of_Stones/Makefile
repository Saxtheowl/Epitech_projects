##
## EPITECH PROJECT, 2024
## Game of Stones
## File description:
## Makefile
##

NAME		=	game_of_stones

SRC		=	main.c		\
			parser.c	\
			graph.c		\
			links.c		\
			plots.c		\
			utils.c

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS		=	-Wall -Wextra -Werror -std=c99 -pedantic
CPPFLAGS	=	-I./include

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re