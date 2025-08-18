NAME = my_ls

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c options.c file_info.c sort.c print.c list.c

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