CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c99 -Iinclude
AR      = ar rcs
RM      = rm -f

NAME    = libmy_printf.a
SRC_DIR = src
TST_DIR = tests

SRC     = $(SRC_DIR)/my_printf.c
OBJ     = $(SRC:.c=.o)

TEST_BIN = test_my_printf
REF_BIN  = printf_reference
TEST_SRC = $(TST_DIR)/main.c
REF_SRC  = $(TST_DIR)/reference.c

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $^

%.o: %.c include/my_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TEST_BIN) $(REF_BIN) $(TST_DIR)/out_my.txt $(TST_DIR)/out_ref.txt

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(TEST_BIN): $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lmy_printf -o $@

$(REF_BIN): $(REF_SRC)
	$(CC) $(CFLAGS) $(REF_SRC) -o $@

test: $(TEST_BIN) $(REF_BIN)
	./$(TEST_BIN) > $(TST_DIR)/out_my.txt
	./$(REF_BIN) > $(TST_DIR)/out_ref.txt
	diff -u $(TST_DIR)/out_ref.txt $(TST_DIR)/out_my.txt
	@echo "my_printf: tests OK"

.PHONY: all clean fclean re test
