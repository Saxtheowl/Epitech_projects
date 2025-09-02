##
## EPITECH PROJECT, 2025
## Strace_roro
## File description:
## Makefile
##

NAME	=	strace

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/args.c \
		$(SRC_DIR)/tracer.c \
		$(SRC_DIR)/arch_x86_64.c \
		$(SRC_DIR)/mem.c \
		$(SRC_DIR)/format.c \
		$(SRC_DIR)/syscalls.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
