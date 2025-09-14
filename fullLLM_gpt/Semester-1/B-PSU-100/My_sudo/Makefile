CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror
CPPFLAGS= -Iinclude
LDFLAGS =

NAME    = my_sudo
SRC     = src/main.c src/solver.c src/io.c
OBJ     = $(SRC:.c=.o)

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	sh tests/test.sh

