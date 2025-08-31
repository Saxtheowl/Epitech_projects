##
## EPITECH PROJECT, 2025
## My_paint - Makefile
##

NAME	=	my_paint
SRC	=	$(wildcard src/*.c)
OBJ	=	$(SRC:.c=.o)
INCLUDE	=	include
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
TEST_NAME	=	unit_tests
TEST_SRC	=	$(wildcard tests/*.c)
TEST_FLAGS	=	$(CFLAGS) --coverage
TEST_LDFLAGS	=	--coverage -lcriterion

.PHONY: all clean fclean re tests_run run

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run: $(NAME)
	./$(NAME)
tests_run: CFLAGS=$(TEST_FLAGS)
tests_run: $(OBJ) $(TEST_SRC)
	$(CC) -o $(TEST_NAME) $(OBJ) $(TEST_SRC) $(TEST_LDFLAGS)
	./$(TEST_NAME)
	- gcovr -b -e tests --print-summary
clean:
	rm -f $(OBJ) $(TEST_NAME) *.gcno *.gcda *.gcov
fclean: clean
	rm -f $(NAME)
re: fclean all

