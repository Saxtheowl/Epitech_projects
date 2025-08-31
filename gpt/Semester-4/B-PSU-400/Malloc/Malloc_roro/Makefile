##
## EPITECH PROJECT, 2025
## Malloc
## File description:
##   Build shared lib libmy_malloc.so
##

NAME	=	libmy_malloc.so

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	\
	$(SRC_DIR)/malloc.c \
	$(SRC_DIR)/free.c \
	$(SRC_DIR)/realloc.c \
	$(SRC_DIR)/calloc.c \
	$(SRC_DIR)/arena.c \
	$(SRC_DIR)/utils.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-fPIC -Wall -Wextra -I$(INC_DIR)
LDFLAGS	=	-shared

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f unit_tests tester
	rm -f *.gcno *.gcda *.gcov

re: fclean all

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(OBJ) $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(OBJ) $(TEST_DIR)/test_basic.o -lcriterion

tests_run: unit_tests
	./unit_tests

tester: $(NAME)
	$(CC) -I$(INC_DIR) -L. -o tester $(TEST_DIR)/tester.c -lmy_malloc

.PHONY: all clean fclean re tests_run

