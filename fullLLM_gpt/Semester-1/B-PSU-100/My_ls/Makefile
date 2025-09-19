CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -Werror
CPPFLAGS= -Iinclude
LDFLAGS =

NAME    = my_ls
SRC     = src/main.c src/ls.c src/print.c src/sort.c
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
