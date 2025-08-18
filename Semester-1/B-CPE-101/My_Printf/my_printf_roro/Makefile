NAME = libmy.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = my_printf.c utils.c format_parser.c format_handlers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re