NAME = my_sokoban

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# LDFLAGS = -lncurses

SRC = main.c utils.c map.c display.c game.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) # $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re