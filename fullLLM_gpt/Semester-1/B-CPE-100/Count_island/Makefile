CC		?=	gcc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
NAME		=	count_island
SRC		=	src/count_island.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) main.o
	$(CC) $(OBJ) main.o -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@tests/test.sh

.PHONY: all clean fclean re test
