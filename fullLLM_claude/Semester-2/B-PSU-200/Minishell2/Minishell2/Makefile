CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99
NAME = mysh

SRCDIR = .
SOURCES = main.c parser.c executor.c builtins.c utils.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re