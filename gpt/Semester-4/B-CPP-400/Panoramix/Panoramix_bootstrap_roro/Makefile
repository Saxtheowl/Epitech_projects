##
## EPITECH PROJECT, 2025
## Panoramix_bootstrap_roro
## File description:
##   Build rules
##

NAME	=	panoramix_bootstrap

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	$(SRC_DIR)/main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(INC_DIR)
LDFLAGS	=	-pthread

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

TU_OBJ	=	$(filter-out $(SRC_DIR)/main.o,$(OBJ))

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion -pthread
unit_tests:	$(TU_OBJ) $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(TU_OBJ) $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run
