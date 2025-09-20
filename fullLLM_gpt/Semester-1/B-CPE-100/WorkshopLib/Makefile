CC		?=	gcc
AR		?=	ar
RANLIB	?=	ranlib
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
NAME		=	lib/libmy.a
SRC		=	$(wildcard lib/my/*.c)
OBJ		=	$(SRC:.c=.o)
TEST_BIN	=	tests/unit

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p lib
	$(AR) rc $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

clean:
	$(RM) $(OBJ) $(TEST_BIN) tests/unit_cases.c

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@tests/test.sh

.PHONY: all clean fclean re test
