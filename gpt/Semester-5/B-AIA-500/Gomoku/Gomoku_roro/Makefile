##
## EPITECH PROJECT, 2025
## Gomoku_roro
## File description:
##   Build rules
##

NAME	=	gomoku_roro

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(INC_DIR)
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run

