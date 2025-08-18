NAME = my_top

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c options.c system_info.c processes.c display.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re