##
## EPITECH PROJECT, 2025
## Groundhog_roro
## File description:
## Makefile
##

NAME	=	groundhog

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.c \
		$(SRC_DIR)/args.c \
		$(SRC_DIR)/stats.c \
		$(SRC_DIR)/weird.c \
		$(SRC_DIR)/io.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I$(INC_DIR)
LDFLAGS	=	-lm

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

unit_tests: CFLAGS += --coverage -I$(INC_DIR)
unit_tests: LDFLAGS += -lcriterion -lgcov
unit_tests: $(filter-out $(SRC_DIR)/main.c,$(SRC)) $(TEST_DIR)/test_dummy.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

tests_run: unit_tests
	./unit_tests || true
	gcovr --exclude tests --branches --print-summary || true

.PHONY: all clean fclean re tests_run unit_tests
