NAME	=	firtree

SRC	=	src/main.c \
		src/tree.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test

test: all
	@tests/test.sh


# Added by auto_report.py
.PHONY: test
TEST_SCRIPT=./scripts/test.sh

test:
	@if [ -x $$(echo $(TEST_SCRIPT)) ]; then \
		$$(echo $(TEST_SCRIPT)); \
	else \
		echo 'No tests script found'; \
	fi
