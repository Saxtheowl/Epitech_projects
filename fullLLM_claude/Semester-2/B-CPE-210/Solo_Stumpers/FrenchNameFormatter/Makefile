##
## EPITECH PROJECT, 2024
## French Name Formatter
## File description:
## Makefile for frenchNameFormatter project
##

NAME	= frenchNameFormatter

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