NAME	=	star

SRC	=	src/main.c \
		src/star.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

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
