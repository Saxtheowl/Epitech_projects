##
## EPITECH PROJECT, 2024
## Bistro-matic
## File description:
## Makefile for bistro-matic calculator
##

NAME	= calc

SRC	= main.c \
	  eval_expr.c \
	  my_utils.c

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