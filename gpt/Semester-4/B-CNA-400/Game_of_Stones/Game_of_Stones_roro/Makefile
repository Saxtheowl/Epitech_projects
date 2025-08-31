##
## EPITECH PROJECT, 2025
## Game_of_Stones Makefile
## File description:
##   Build rules
##

NAME	=	game_of_stones

SRC_DIR	=	src
INC_DIR	=	include
TEST_DIR	=	tests

SRC	=	\
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/strings.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/graph.c \
	$(SRC_DIR)/links_mode.c \
	$(SRC_DIR)/plots_mode.c \
	$(SRC_DIR)/output.c

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
unit_tests:	$(OBJ) $(TEST_DIR)/test_basic.o
	$(CC) -o $@ $(OBJ) $(TEST_DIR)/test_basic.o $(LDFLAGS)

tests_run: unit_tests
	./unit_tests

.PHONY: all clean fclean re tests_run

