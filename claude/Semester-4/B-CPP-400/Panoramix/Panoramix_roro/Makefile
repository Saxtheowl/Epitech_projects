##
## EPITECH PROJECT, 2025
## Panoramix
## File description:
## Makefile for Panoramix project
##

SRC	= panoramix.c

OBJ	= $(SRC:.c=.o)

NAME	= panoramix

CFLAGS	= -Wall -Wextra -Werror -pthread

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re