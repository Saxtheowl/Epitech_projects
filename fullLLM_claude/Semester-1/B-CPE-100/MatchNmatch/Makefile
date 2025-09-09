NAME_MATCH = match
NAME_NMATCH = nmatch

SRC_MATCH = match.c
SRC_NMATCH = nmatch.c

OBJ_MATCH = $(SRC_MATCH:.c=.o)
OBJ_NMATCH = $(SRC_NMATCH:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I./include

LDFLAGS = -L./lib/my -lmy

CC = gcc

all: $(NAME_MATCH) $(NAME_NMATCH)

lib:
	cd lib/my && ./build.sh

$(NAME_MATCH): lib $(OBJ_MATCH)
	$(CC) $(CFLAGS) -o $(NAME_MATCH) $(OBJ_MATCH) tests/match_main.c $(LDFLAGS)

$(NAME_NMATCH): lib $(OBJ_NMATCH)
	$(CC) $(CFLAGS) -o $(NAME_NMATCH) $(OBJ_NMATCH) tests/nmatch_main.c $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_MATCH) $(OBJ_NMATCH)
	rm -f lib/my/libmy.a

fclean: clean
	rm -f $(NAME_MATCH) $(NAME_NMATCH)

re: fclean all

test: all
	./tests/test.sh

.PHONY: all clean fclean re lib test