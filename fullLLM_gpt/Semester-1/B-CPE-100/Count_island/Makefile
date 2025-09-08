NAME	=	count_island

SRC	=	src/count_island.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME): $(OBJ) main.o
	$(CC) $(OBJ) main.o -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test

test: all
	@tests/test.sh
