##
## EPITECH PROJECT, 2024
## Spongebob Case Checker
## File description:
## Makefile for spongebob_case_checker project
##

NAME	= spongebob_case_checker

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