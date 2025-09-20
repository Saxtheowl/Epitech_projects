CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99
CPPFLAGS= -Iinclude

NAME    = rush3
SRC     = src/main.c \
          src/rush3.c \
          src/patterns.c \
          src/utils.c \
          src/str_utils.c
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
