CC		?=	gcc
CFLAGS		+=	-Wall -Wextra -Werror
CPPFLAGS	+=	-Iinclude
NAME		=	star
SRC		=	src/main.c \
			src/star.c \
			src/my_putchar.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: $(NAME)
	@tests/test.sh

.PHONY: all clean fclean re test
