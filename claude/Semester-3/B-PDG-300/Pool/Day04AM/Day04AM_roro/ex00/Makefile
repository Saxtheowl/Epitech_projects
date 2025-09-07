CC = gcc
CFLAGS = -std=gnu17 -Wall -Wextra
NAME = z
SRC = z.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re