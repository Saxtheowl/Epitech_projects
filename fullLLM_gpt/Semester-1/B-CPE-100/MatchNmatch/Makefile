CC		?=	gcc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
SRC		=	src/match.c \
			src/nmatch.c
OBJ		=	$(SRC:.c=.o)
NAME_MATCH	=	match
NAME_NMATCH	=	nmatch
TEST_BIN	=	tests/harness

all: $(OBJ)

clean:
	$(RM) $(OBJ) $(TEST_BIN) tests/harness.c

fclean: clean
	$(RM) $(NAME_MATCH) $(NAME_NMATCH)

re: fclean all

test: $(OBJ)
	@tests/test.sh

.PHONY: all clean fclean re test
