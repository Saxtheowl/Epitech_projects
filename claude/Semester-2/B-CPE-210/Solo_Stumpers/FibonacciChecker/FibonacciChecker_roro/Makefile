NAME = fibonacci_checker
SRC = src/fibonacci_checker.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra

all: $(NAME)
$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re