##
## EPITECH PROJECT, 2024
## EvalExpr
## File description:
## Makefile for eval_expr
##

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
NAME    = eval_expr

SRC     = main.c \
          eval_expr.c \
          my_utils.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re