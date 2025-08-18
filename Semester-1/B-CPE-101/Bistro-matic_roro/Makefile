NAME = bistromatic

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = eval_expr.c utils.c bigint.c parser.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) ../Bistro-matic/main.c

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re