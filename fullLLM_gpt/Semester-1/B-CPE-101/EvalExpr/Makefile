CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror
CPPFLAGS= -Iinclude

NAME    = eval_expr
SRC     = main.c \
          src/eval_expr.c \
          src/io.c
OBJ     = $(SRC:.c=.o)

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	sh tests/test.sh
