NAME = count_island

SRC = count_island.c test_map.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I./include

LDFLAGS = -L./lib/my -lmy

CC = gcc

all: $(NAME)

lib:
	cd lib/my && ./build.sh

$(NAME): lib $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f lib/my/libmy.a

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./tests/test.sh

.PHONY: all clean fclean re lib test