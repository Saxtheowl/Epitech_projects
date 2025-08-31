##
## EPITECH PROJECT, 2025
## Palindrome - Makefile
## File description:
## Standard Makefile with tests
##

NAME	=	palindrome

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

INCLUDE	=	include

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS	=

TEST_NAME	=	unit_tests
TEST_SRC	=	$(wildcard tests/*.c)
TEST_FLAGS	=	$(CFLAGS) --coverage
TEST_LDFLAGS	=	$(LDFLAGS) --coverage -lcriterion

.PHONY: all clean fclean re tests_run

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tests_run: CFLAGS=$(TEST_FLAGS)
tests_run: LDFLAGS=$(TEST_LDFLAGS)
tests_run: $(OBJ) $(TEST_SRC)
	$(CC) -o $(TEST_NAME) $(OBJ) $(TEST_SRC) $(TEST_LDFLAGS)
	./$(TEST_NAME)
	- gcovr -b -e tests --print-summary

clean:
	rm -f $(OBJ)
	rm -f *.gcno *.gcda *.gcov
	rm -f $(TEST_NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

