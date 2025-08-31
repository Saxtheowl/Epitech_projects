##
## EPITECH PROJECT, 2025
## Panoramix
## File description:
##   Build rules
##

NAME	=	panoramix

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	\
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/args.c \
	$(SRC_DIR)/sim.c \
	$(SRC_DIR)/villager.c \
	$(SRC_DIR)/druid.c \
	$(SRC_DIR)/sync.c \
	$(SRC_DIR)/strings.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I$(INC_DIR) -pthread
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

unit_tests: CFLAGS += --coverage
unit_tests: LDFLAGS += -lcriterion
unit_tests:	$(OBJ) $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(OBJ) $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run

