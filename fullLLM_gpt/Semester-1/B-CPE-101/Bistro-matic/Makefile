CC      ?= gcc
CFLAGS  += -Wall -Wextra -Werror -std=c99
CPPFLAGS+= -Iinclude
NAME    = calc
SRC     = main.c \
          src/utils.c \
          src/bigint.c \
          src/parser.c \
          src/eval_expr.c
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@tests/test.sh

.PHONY: all clean fclean re test
