CC = gcc
CFLAGS = -std=gnu17 -Wall -Wextra
NAME = z
TEST_NAME = test_z

SRC = z.c
TEST_SRC = test_z.c
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(TEST_NAME): $(TEST_OBJ) $(NAME)
	$(CC) $(TEST_OBJ) -o $(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_NAME)
	./$(TEST_NAME)

tests_run: test

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test tests_run