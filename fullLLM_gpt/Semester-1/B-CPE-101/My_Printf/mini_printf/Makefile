CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -Iinclude
AR      = ar rcs
RM      = rm -f

NAME    = libmini_printf.a
SRC_DIR = src
INC_DIR = include
TST_DIR = tests

SRC     = $(SRC_DIR)/mini_printf.c \
          $(SRC_DIR)/print.c
OBJ     = $(SRC:.c=.o)

TEST_BIN = test_mini_printf
TEST_SRC = $(TST_DIR)/main.c

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c $(INC_DIR)/mini_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_BIN)

re: fclean all

$(TEST_BIN): $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lmini_printf -o $@

test: $(TEST_BIN)
	./$(TEST_BIN) > $(TST_DIR)/out.txt
	diff -u $(TST_DIR)/expected.txt $(TST_DIR)/out.txt
	@echo "mini_printf: tests OK"

.PHONY: all clean fclean re test

