CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror
CPPFLAGS= -Iinclude
LDFLAGS =

NAME    = bsq
SRC     = src/main.c src/bsq.c src/io.c src/map.c
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



# Added by auto_report.py
.PHONY: test
TEST_SCRIPT=./scripts/test.sh

test:
	@if [ -x $$(echo $(TEST_SCRIPT)) ]; then \
		$$(echo $(TEST_SCRIPT)); \
	else \
		echo 'No tests script found'; \
	fi
