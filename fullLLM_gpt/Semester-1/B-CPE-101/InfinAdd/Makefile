CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99
CPPFLAGS= -Iinclude

NAME    = infin_add
SRC     = src/main.c \
          src/infin_add.c \
          src/utils.c
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
