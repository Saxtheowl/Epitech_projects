CC		?=	gcc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
SRC		=	src/rush.c
OBJ		=	$(SRC:.c=.o)
TEST_BIN	=	tests/harness

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(TEST_BIN) tests/harness.c

fclean: clean

re: fclean all

test: all
	@tests/test.sh

.PHONY: all clean fclean re test
