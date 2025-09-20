CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99 -Iinclude
SRC     = src/main.c src/compress.c src/io.c
OBJ     = $(SRC:.c=.o)
BIN     = antman

.PHONY: all clean fclean re test

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c include/antman.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)

re: fclean all

test:
	sh tests/test.sh
