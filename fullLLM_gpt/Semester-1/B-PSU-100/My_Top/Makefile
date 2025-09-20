CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror
CPPFLAGS= -Iinclude
LDFLAGS =

NAME    = my_top
SRC     = src/main.c src/proc.c src/format.c
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
