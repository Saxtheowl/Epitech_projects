##
## EPITECH PROJECT, 2024
## Text to Multi Tap
## File description:
## Makefile for text_to_multi_tap project
##

NAME	= text_to_multi_tap

SRC	= main.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re