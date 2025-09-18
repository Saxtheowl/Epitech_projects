CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -Iinclude
AR      = ar rcs
RM      = rm -f

NAME    = libmy_printf.a
SRC_DIR = src
INC_DIR = include
TST_DIR = tests

SRC     = $(SRC_DIR)/my_printf.c \
          $(SRC_DIR)/print_num.c \
          $(SRC_DIR)/print_hex.c \
          $(SRC_DIR)/print_oct.c \
          $(SRC_DIR)/print_ptr.c
OBJ     = $(SRC:.c=.o)

TEST_BIN = test_my_printf
TEST_SRC = $(TST_DIR)/main.c

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c $(INC_DIR)/my_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_BIN)

re: fclean all

$(TEST_BIN): $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lmy_printf -o $@

test: $(TEST_BIN)
	./$(TEST_BIN) > $(TST_DIR)/out.txt
	diff -u $(TST_DIR)/expected.txt $(TST_DIR)/out.txt
	@echo "my_printf: tests OK"

.PHONY: all clean fclean re test

